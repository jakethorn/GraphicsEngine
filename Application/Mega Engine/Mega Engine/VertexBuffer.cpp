#include "VertexBuffer.h"

#include <assimp/importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <d3d11.h>

#include <map>
#include <sstream>

#include "Common.h"
#include "DebugConsole.h"
#include "Direct3D.h"
#include "Factory.h"

using std::stringstream;

vector<string> filenames;
vector<unsigned int> indexCounts;
vector<unsigned int> startIndexLocations;
vector<unsigned int> baseVertexLocations;

// new

struct BufferData
{
	unsigned int indexCounts;
	unsigned int startIndexLocation;
	unsigned int baseVertexLocation;
};

std::map<string, BufferData> bufferDataMap;

// new

void CreateBufferData(string filename, vector<float> &positions, vector<float> &normals, vector<unsigned int> &indices)
{
	static Assimp::Importer sImporter;
	const aiScene * const scene = sImporter.ReadFile(filename,
		aiProcess_ConvertToLeftHanded	|
		aiProcess_JoinIdenticalVertices |
		aiProcess_Triangulate			|
		aiProcess_GenNormals
	);

	stringstream ss;

	static int sMeshCount = 1;
	ss << "\n";
	ss << "Creating mesh: " << sMeshCount << "\n";
	ss << "Filename: " << filename << "\n";
	sMeshCount++;

	const aiMesh * const mesh = scene->mMeshes[0]; 
	ss << "Has positions: " << mesh->HasPositions() << "\n";
	ss << "Has normals:   " << mesh->HasNormals() << "\n";
	ss << "Has faces:     " << mesh->HasFaces() << "\n";

	console::Print(ss.str());

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		positions.push_back(mesh->mVertices[i].x);
		positions.push_back(mesh->mVertices[i].y);
		positions.push_back(mesh->mVertices[i].z);

		normals.push_back(mesh->mNormals[i].x);
		normals.push_back(mesh->mNormals[i].y);
		normals.push_back(mesh->mNormals[i].z);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
}

void vb::Init(vector<string> _filenames)
{
	//
	//
	//

	filenames = _filenames;

	//
	//
	//

	vector<float> aAllPositions;
	vector<float> aAllNormals;
	vector<unsigned int> aAllIndices;

	for (auto &filename : filenames)
	{
		vector<float> aPositions;
		vector<float> aNormals;
		vector<unsigned int> aIndices;
		CreateBufferData(filename, aPositions, aNormals, aIndices);

		//

		indexCounts.push_back(aIndices.size());
		startIndexLocations.push_back(aAllIndices.size());
		baseVertexLocations.push_back(aAllPositions.size() / 3);

		//

		aAllPositions.insert(aAllPositions.end(), aPositions.begin(), aPositions.end());
		aAllNormals.insert(aAllNormals.end(), aNormals.begin(), aNormals.end());
		aAllIndices.insert(aAllIndices.end(), aIndices.begin(), aIndices.end());
	}

	//
	//
	//

	static ID3D11Device			* const device = d3d::GetDevice();
	static ID3D11DeviceContext	* const context = d3d::GetImmediateContext();

	ID3D11Buffer *cubeBuffers[2];
	cubeBuffers[0] = factory::CreateVertexBuffer(false, false, &aAllPositions[0], aAllPositions.size() * sizeof(float));
	cubeBuffers[1] = factory::CreateVertexBuffer(false, false, &aAllNormals[0],	aAllNormals.size() * sizeof(float));

	const UINT strides[] { 3 * sizeof(float), 3 * sizeof(float) };
	const UINT offsets[] { 0, 0 };
	context->IASetVertexBuffers(0, 2, &cubeBuffers[0], &strides[0], &offsets[0]);
	ReleaseCOM(cubeBuffers[0]);
	ReleaseCOM(cubeBuffers[1]);

	//
	//
	//

	ID3D11Buffer *indexBuffer = factory::CreateIndexBuffer(false, &aAllIndices[0], aAllIndices.size() * sizeof(unsigned int));

	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	ReleaseCOM(indexBuffer);

	// init map
	for ( int i = 0; i < filenames.size(); i++ )
		bufferDataMap[filenames[i]] = { indexCounts[i], startIndexLocations[i], baseVertexLocations[i] };
}

void vb::Draw(string shape)
{
	static ID3D11DeviceContext * const context = d3d::GetImmediateContext();

	auto cache = bufferDataMap.find( shape )->second;

	context->DrawIndexed(
		cache.indexCounts, 
		cache.startIndexLocation, 
		cache.baseVertexLocation
	);
}