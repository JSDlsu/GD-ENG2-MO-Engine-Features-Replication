#include "BNS_Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "BNS_GraphicsEngine.h"
#include "VertexMesh.h"

BNS_Mesh::BNS_Mesh(const wchar_t* full_path) : BNS_Resource(full_path)
{
	// data structure for the list of vertices, texture coordinates, and so on..
	tinyobj::attrib_t attribs;
	// group of meshes stored in the obj file
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	// warning exceptions for functions
	std::string warn;
	std::string err;

	// convert const wchar_t into simple string type
	std::wstring ws(full_path);
	std::string inputfile(ws.begin(), ws.end());

	// parse the object model into a data structure
	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty())
		throw std::exception("BNS_Mesh not created successfully");

	if (!res)
		throw std::exception("BNS_Mesh not created successfully");

	if (shapes.size() > 1)
		throw std::exception("BNS_Mesh not created successfully");

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	// reserve the size of our vector in order to speed up the insertion
	int vector_size = 0;
	for (size_t s = shapes.size(); s-- > 0; ) {
		vector_size += shapes[s].mesh.indices.size();
	}
	list_vertices.reserve(vector_size);
	list_indices.reserve(vector_size);

	size_t index_global_offset = 0;

	// get all the retrieved data and process them
	// iterate all of the shapes
	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;

		// iterate all of the face
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			// for each phase we have to get the number of vertices that compose it
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			Vector3D vertices_face[3];
			Vector2D texcoords_face[3];

			// iterate all of those vertices
			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				// indices of each shape
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				// BNS_vertex_tex coordinates
				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				// texture coordinates
				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;

				if (attribs.texcoords.size())
				{
					tx = attribs.texcoords[(int)index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[(int)index.texcoord_index * 2 + 1];
				}
				vertices_face[v] = Vector3D(vx, vy, vz);
				texcoords_face[v] = Vector2D(tx, ty);

				tinyobj::real_t nx = 0;
				tinyobj::real_t ny = 0;
				tinyobj::real_t nz = 0;
				if (attribs.normals.size())
				{
					nx = attribs.normals[index.normal_index * 3 + 0];
					ny = attribs.normals[index.normal_index * 3 + 1];
					nz = attribs.normals[index.normal_index * 3 + 2];
				}

				// passing the attributes to our BNS_vertex_tex _mesh; then push it to the vector
				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty),
					Vector3D(nx, ny, nz));
				list_vertices.push_back(vertex);

				// passing the attributes to our index _mesh; then push it to the vector
				list_indices.push_back((unsigned int)index_global_offset + v);
			}

			index_offset += num_face_verts;
			index_global_offset += num_face_verts;
		}
	}

	// create the index buffer
	m_ib = BNS_GraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer(&list_indices[0],
		(UINT)list_indices.size());

	// create a BNS_vertex_tex buffer
	m_vb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(&list_vertices[0],
		sizeof(VertexMesh), (UINT)list_vertices.size(),
		BNS_InputLayoutType::MESH);

}

BNS_Mesh::~BNS_Mesh()
{
}

const VertexBufferPtr& BNS_Mesh::getVertexBuffer()
{
	return m_vb;
}

const IndexBufferPtr& BNS_Mesh::getIndexBuffer()
{
	return  m_ib;
}