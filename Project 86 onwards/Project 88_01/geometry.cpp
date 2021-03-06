#include "geometry.h"
#include <glm\gtx\constants.hpp>

void initialiseBuffers(geometry* geom)
{
	if (geom->vertices.size() > 0) //if we have vertices, then add to the vertex array object
		createVertexBuffer(geom);

	if (geom->normals.size() > 0)//if we have normals, then add to the vertex array object
		createNormalBuffer(geom);

	if (geom->texcoords.size() > 0)//if we have texcoords, then add to the vertex array object
		createTexBuffer(geom);

	if (geom->colours.size() > 0)
		createColourBuffer(geom);

	glBindVertexArray(0);
}

//create box code
glm::vec3 box_vertices[8] =
{
	glm::vec3(-1.0f, 1.0f, 1.0f),		// 0
	glm::vec3(1.0f, 1.0f, 1.0f),		// 1
	glm::vec3(1.0f, -1.0f, 1.0f),		// 2
	glm::vec3(-1.0f, -1.0f, 1.0f),		// 3
	glm::vec3(1.0f, 1.0f, -1.0f),		// 4
	glm::vec3(-1.0f, 1.0f, -1.0f),		// 5
	glm::vec3(-1.0f, -1.0f, -1.0f),		// 6
	glm::vec3(1.0f, -1.0f, -1.0f)		// 7

};
glm::vec3 box_normals[8] =
{
	glm::normalize(glm::vec3(-1.0f, 1.0f, 1.0f)),		// 0
	glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)),		// 1
	glm::normalize(glm::vec3(1.0f, -1.0f, 1.0f)),		// 2
	glm::normalize(glm::vec3(-1.0f, -1.0f, 1.0f)),		// 3
	glm::normalize(glm::vec3(1.0f, 1.0f, -1.0f)),		// 4
	glm::normalize(glm::vec3(-1.0f, 1.0f, -1.0f)),		// 5
	glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)),		// 6
	glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f))		// 7
};

glm::vec2 box_texcoords[6] =
{
	glm::vec2(0.0f, 1.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(0.0f, 0.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),
};

unsigned int box_indices[36] = 
{
	// Side 1
	0, 1, 3,
	1, 2, 3,
	//Side 2
	1, 4, 2,
	4, 7, 2,
	// Side 3
	4, 5, 7,
	5, 6, 7,
	// Side 4
	5, 0, 6,
	0, 3, 6,
	// Side 5
	5, 4, 0,
	4, 1, 0,
	// Side 6
	3, 2, 6,
	2, 7, 6
};

geometry* createBox()
{
	geometry* geom = new geometry();
	for(int i = 0; i < 36; ++i)
	{
		geom->vertices.push_back(box_vertices[box_indices[i]]);
		geom->normals.push_back(box_normals[box_indices[i]]);
		geom->texcoords.push_back(box_texcoords[i % 6]);
	}
	for (int i = 0; i < 36; ++i)
		geom->indices.push_back(box_indices[i]);

	initialiseBuffers(geom);
	
	return geom;
}

//tetrahedron code
glm::vec3 tetrahedron_vertices[4] = 
{
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(0.0f, -1.0f, -1.0f)
};

glm::vec2 tetrahedron_texcoords[3] = 
{
	glm::vec2(0.5f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f)
};

glm::vec3 tetrahedron_normals[4] = 
{
	glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)),
	glm::normalize(glm::vec3(-1.0f, -1.0f, 1.0f)),
	glm::normalize(glm::vec3(1.0f, -1.0f, 1.0f)),
	glm::normalize(glm::vec3(0.0f, -1.0f, -1.0f))
};

unsigned int tetrahedron_indices[12] = 
{
	// Side 1
	0, 2, 1, 
	// Side 2
	0, 3, 2, 
	//Side 3
	0, 1, 3, 
	// Bottom
	1, 2, 3
};

geometry* createTetrahedron() 
{
	geometry* geom = new geometry();
	for (int i = 0; i < 12; ++i)
	{
		geom->vertices.push_back(tetrahedron_vertices[tetrahedron_indices[i]]);
		geom->normals.push_back(tetrahedron_normals[tetrahedron_indices[i]]);
		geom->texcoords.push_back(tetrahedron_texcoords[i % 3]);
	}
		
	initialiseBuffers(geom);
	return geom;
}

//pyramid code
glm::vec3 pyramid_vertices[5] = 
{
	glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)),
	glm::normalize(glm::vec3(-1.0f, -1.0f, 1.0f)),
	glm::normalize(glm::vec3(1.0f, -1.0f, 1.0f)),
	glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f)),
	glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f))
};

glm::vec3 pyramid_normals[5] = 
{
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f)
};

glm::vec2 pyramid_texcoords[18] = 
{
	//face 1
	glm::vec2(0.5f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),

	//Face 2
	glm::vec2(0.5f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),

	//Face 3
	glm::vec2(0.5f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),

	//Face 4
	glm::vec2(0.5f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),

	//Bottom
	glm::vec2(0.0f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 0.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(1.0f, 0.0f),
};

unsigned int pyramid_indices[18] = 
{
	// Side 1
	0, 2, 1,
	// Side 2
	0, 3, 2,
	// Side 3
	0, 4, 3, 
	// Side 4
	0, 1, 4, 
	// Bottom
	1, 3, 4, 
	1, 2, 3
};

geometry* createPyramid()
{
	geometry* geom = new geometry();
	for (int i = 0; i < 18; ++i)
	{
		geom->vertices.push_back(pyramid_vertices[pyramid_indices[i]]);
		geom->normals.push_back(pyramid_normals[pyramid_indices[i]]);
		geom->texcoords.push_back(pyramid_texcoords[i]);
	}

	initialiseBuffers(geom);
	return geom;
}

//create a disk
geometry* createDisk(int slices)
{
	geometry* geom = new geometry();
	glm::vec3 centre(0.0f, 0.0f, 0.0f);
	glm::vec3 vertex_prev(1.0f, 0.0, 0.0f);
	glm::vec3 vertex_current;
	float deltaAngle = (2.0f * glm::pi<float>()) / slices;
	for (int i = 1; i <= slices; ++i)
	{
		vertex_current = glm::vec3(cos(i * deltaAngle), 0.0f, sin(i * deltaAngle));
		geom->vertices.push_back(centre);
		geom->vertices.push_back(vertex_prev);
		geom->vertices.push_back(vertex_current);
		for (int j = 0; j < 3; ++j)
			geom->normals.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f) + (glm::vec2(vertex_prev.x, vertex_prev.z) / 2.0f));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f) + (glm::vec2(vertex_current.x, vertex_current.z) / 2.0f));
		vertex_prev = vertex_current;
	}

	initialiseBuffers(geom);
	return geom;
}

//create cylinder
geometry* createCylinder(int stacks, int slices)
{
	geometry* geom = new geometry();
	//Create top
	glm::vec3 centre(0.0f, 1.0f, 0.0f);
	glm::vec3 vertex_prev(1.0f, 1.0, 0.0f);
	glm::vec3 vertex_current;
	float deltaAngle = (2 * glm::pi<float>()) / slices;
	for (int i = 1; i <= slices; ++i)
	{
		vertex_current = glm::vec3(cos(i * deltaAngle), 1.0f, sin(i * deltaAngle));
		geom->vertices.push_back(centre);
		geom->normals.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		geom->vertices.push_back(vertex_prev);
		geom->normals.push_back(glm::normalize(glm::vec3(vertex_prev.x, 1.0f, vertex_prev.z)));
		geom->vertices.push_back(vertex_current);
		geom->normals.push_back(glm::normalize(glm::vec3(vertex_current.x, 1.0f, vertex_current.z)));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f) + (glm::vec2(vertex_prev.x, vertex_prev.z) / 2.0f));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f) + (glm::vec2(vertex_current.x, vertex_current.z) / 2.0f));
		vertex_prev = vertex_current;
	}
	
	//create Bottom
	centre = glm::vec3(0.0f, -1.0f, 0.0f);
	vertex_prev = glm::vec3(1.0f, -1.0f, 0.0f);
	for (int i = 1; i <= slices; ++i)
	{
		vertex_current = glm::vec3(cos(i * deltaAngle), -1.0f, sin(i * deltaAngle));
		geom->vertices.push_back(centre);
		geom->normals.push_back(glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)));
		geom->vertices.push_back(vertex_prev);
		geom->normals.push_back(glm::normalize(glm::vec3(vertex_prev.x, -1.0f, vertex_prev.z)));
		geom->vertices.push_back(vertex_current);
		geom->normals.push_back(glm::normalize(glm::vec3(vertex_current.x, -1.0f, vertex_current.z)));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f) + (glm::vec2(vertex_prev.x, vertex_prev.z) / 2.0f));
		geom->texcoords.push_back(glm::vec2(0.5f, 0.5f) + (glm::vec2(vertex_current.x, vertex_current.z) / 2.0f));
		vertex_prev = vertex_current;
	}

	//Create Stack
	glm::vec3 vertices[4];
	float deltaHeight = 2.0f / stacks;
	float deltaWidth = 1.0f / slices;
	for (int i = 0; i < stacks; ++i)
	{
		for (int j = 0; j < slices; ++j)
		{
			vertices[0] = glm::vec3(cos(j * deltaAngle), 1.0f - (deltaHeight * i), sin(j * deltaAngle));
			vertices[1] = glm::vec3(cos((j + 1) * deltaAngle), 1.0f - (deltaHeight * i), sin((j + 1) * deltaAngle));
			vertices[2] = glm::vec3(cos(j * deltaAngle), 1.0f - (deltaHeight * (i + 1)), sin(j * deltaAngle));
			vertices[3] = glm::vec3(cos((j + 1) * deltaAngle), 1.0f - (deltaHeight *(i + 1)), sin((j + 1) * deltaAngle));
			//triangle 1
			geom->vertices.push_back(vertices[0]);
			geom->normals.push_back(glm::normalize(glm::vec3(vertices[0].x, 0.0f, vertices[0].z)));
			geom->texcoords.push_back(glm::vec2(deltaWidth * j, 1.0f - ((deltaHeight * i) / 2)));
			geom->vertices.push_back(vertices[3]);
			geom->normals.push_back(glm::normalize(glm::vec3(vertices[3].x, 0.0f, vertices[3].z)));
			geom->texcoords.push_back(glm::vec2(deltaWidth * (j + 1), 1.0f - ((deltaHeight * (i + 1)) / 2)));
			geom->vertices.push_back(vertices[2]);
			geom->normals.push_back(glm::normalize(glm::vec3(vertices[2].x, 0.0f, vertices[2].z)));
			geom->texcoords.push_back(glm::vec2(deltaWidth * j, 1.0f - ((deltaHeight * (i + 1)) / 2)));
			//triangle 2
			geom->vertices.push_back(vertices[0]);
			geom->normals.push_back(glm::normalize(glm::vec3(vertices[0].x, 0.0f, vertices[0].z)));
			geom->texcoords.push_back(glm::vec2(deltaWidth * j, 1.0f - ((deltaHeight * (i + 1)) / 2)));
			geom->vertices.push_back(vertices[1]);
			geom->normals.push_back(glm::normalize(glm::vec3(vertices[1].x, 0.0f, vertices[1].z)));
			geom->texcoords.push_back(glm::vec2(deltaWidth * (j + 1), 1.0f - ((deltaHeight * i) / 2)));
			geom->vertices.push_back(vertices[3]);
			geom->normals.push_back(glm::normalize(glm::vec3(vertices[3].x, 0.0f, vertices[3].z)));
			geom->texcoords.push_back(glm::vec2(deltaWidth * (j + 1), 1.0f - ((deltaHeight * (i + 1)) / 2)));
		}
	}

	initialiseBuffers(geom);
	return geom;
}

//Create sphere
geometry* createSphere(int stacks, int slices)
{
	geometry* geom = new geometry();
	//create required values
	float deltaRho = glm::pi<float>() / stacks;
	float deltaTheta = 2.0f * glm::pi<float>() / slices;
	float deltaT = 1.0f / (float)stacks;
	float deltaS = 1.0f / (float)slices;
	float t = 1.0f;
	float s = 0.0f;
	for (int i = 0; i < stacks; ++i)
	{
		float rho = i * deltaRho;
		glm::vec3 vertices[4];
		glm::vec2 texcoords[4];
		for (int j = 0; j < slices; ++j)
		{
			// Vertex 0 
			float theta = j * deltaTheta; 
			vertices[0] = glm::vec3(-sin(theta) * sin(rho), cos(theta) * sin(rho), cos(rho));
			texcoords[0] = glm::vec2(s, t);
			// Vertex 1
			vertices[1] = glm::vec3(-sin(theta) * sin(rho + deltaRho), cos(theta) * sin(rho + deltaRho), cos(rho + deltaRho));
			texcoords[1] = glm::vec2(s, t - deltaT);
			// Vertex 2
			theta = ((j + 1) == slices) ? 0.0f : (j + 1) * deltaTheta;
			s += deltaS;
			vertices[2] = glm::vec3(-sin(theta) * sin(rho), cos(theta) * sin(rho), cos(rho));
			texcoords[2] = glm::vec2(s, t);
			// Vertex 3
			vertices[3] = glm::vec3(-sin(theta) * sin(rho + deltaRho), cos(theta) * sin(rho + deltaRho), cos(rho + deltaRho));
			texcoords[3] = glm::vec2(s, t - deltaT);

			// Triangle 1
			geom->vertices.push_back(vertices[0]);
			geom->normals.push_back(glm::normalize(vertices[0]));
			geom->texcoords.push_back(texcoords[0]);
			geom->vertices.push_back(vertices[1]);
			geom->normals.push_back(glm::normalize(vertices[1]));
			geom->texcoords.push_back(texcoords[1]);
			geom->vertices.push_back(vertices[2]);
			geom->normals.push_back(glm::normalize(vertices[2]));
			geom->texcoords.push_back(texcoords[2]);
			// Triangle 2
			geom->vertices.push_back(vertices[1]);
			geom->normals.push_back(glm::normalize(vertices[1]));
			geom->texcoords.push_back(texcoords[1]);
			geom->vertices.push_back(vertices[3]);
			geom->normals.push_back(glm::normalize(vertices[3]));
			geom->texcoords.push_back(texcoords[3]);
			geom->vertices.push_back(vertices[2]);
			geom->normals.push_back(glm::normalize(vertices[2]));
			geom->texcoords.push_back(texcoords[2]);
		}
	}

	initialiseBuffers(geom);
	return geom;
}

//create Torus
geometry* createTorus(float radius, int stacks, int slices)
{
	geometry* geom = new geometry();
	float deltaStack = 2.0f * glm::pi<float>() / stacks;
	float deltaSlice = 2.0f * glm::pi<float>() / slices;
	for (int i = 0; i < stacks; ++i)
	{
		float a0 = i * deltaStack;
		float a1 = a0 + deltaStack;
		glm::vec3 vertices[4];
		glm::vec3 normals[4];
		glm::vec2 texcoords[4];
		for (int j = 0; j <= slices; ++j)
		{
			float b = j * deltaSlice;
			float c = cos(j * deltaSlice);
			float r = c + radius;
			vertices[0] = glm::vec3(sin(a0) * r, sin(j * deltaSlice), cos(a0) * r);
			normals[0] = glm::vec3(sin(a0) * c, sin(j * deltaSlice), cos(a0) * c);
			texcoords[0] = glm::vec2((float)i / stacks, (float)j / slices);
			vertices[1] = glm::vec3(sin(a1) * r, sin(j * deltaSlice), cos(a1) * r);
			normals[1] = glm::vec3(sin(a1) * c, sin(j * deltaSlice), cos(a0) * c);
			texcoords[1] = glm::vec2((float)(i + 1) / stacks, (float)j / slices);
			c = cos((j + 1) * deltaSlice);
			r = c + radius;
			vertices[2] = glm::vec3(sin(a0) * r, sin((j + 1) * deltaSlice), cos(a0) * r);
			normals[2] = glm::vec3(sin(a0) * c, sin(j * deltaSlice), cos(a0) * c);
			texcoords[2] = glm::vec2((float)i / stacks, (float)(j + 1) / slices);
			vertices[3] = glm::vec3(sin(a1) * r, sin((j + 1) * deltaSlice), cos(a1) * r);
			normals[3] = glm::vec3(sin(a1) * c, sin(j * deltaSlice), cos(a0) * c);
			texcoords[3] = glm::vec2((float)(i + 1) / stacks, (float)(j + 1) / slices);
			// Triangle 1
			geom->vertices.push_back(vertices[0]);
			geom->normals.push_back(glm::normalize(normals[0]));
			geom->texcoords.push_back(texcoords[0]);
			geom->vertices.push_back(vertices[1]);
			geom->normals.push_back(glm::normalize(normals[1]));
			geom->texcoords.push_back(texcoords[1]);
			geom->vertices.push_back(vertices[2]);
			geom->normals.push_back(glm::normalize(normals[2]));
			geom->texcoords.push_back(texcoords[2]);
			// Triangle 2
			geom->vertices.push_back(vertices[1]);
			geom->normals.push_back(glm::normalize(normals[1]));
			geom->texcoords.push_back(texcoords[1]);
			geom->vertices.push_back(vertices[3]);
			geom->normals.push_back(glm::normalize(normals[3]));
			geom->texcoords.push_back(texcoords[3]);
			geom->vertices.push_back(vertices[2]);
			geom->normals.push_back(glm::normalize(normals[2]));
			geom->texcoords.push_back(texcoords[2]);
		}
	}

	initialiseBuffers(geom);
	return geom;
}

//create Plane
geometry* createPlane(int width, int depth)
{
	geometry* geom = new geometry();
	glm::vec3 vertices[4];
	float deltaWidth = 1.0f * glm::pi<float>() / width;
	float deltaDepth = 1.0f * glm::pi<float>() / depth;
	for (int x = 0; x < width; ++x)
	{
		for (int z = 0; z < depth; ++z)
		{
			vertices[0] = glm::vec3(-((float)width / 2.0f) + x, 0.0f, -((float)depth / 2.0f) + z);
			vertices[1] = glm::vec3(-((float)width / 2.0f) + (x + 1), 0.0f, -((float)depth / 2.0f) + z);
			vertices[2] = glm::vec3(-((float)width / 2.0f) + x, 0.0f, -((float)depth / 2.0f) + (z + 1));
			vertices[3] = glm::vec3(-((float)width / 2.0f) + (x+1), 0.0f, -((float)depth / 2.0f) + (z + 1));
			// Triangle 1
			geom->vertices.push_back(vertices[0]);
			geom->texcoords.push_back(glm::vec2(deltaWidth * x, deltaDepth * z));
			geom->vertices.push_back(vertices[3]);
			geom->texcoords.push_back(glm::vec2(deltaWidth * (x + 1), deltaDepth * (z + 1)));
			geom->vertices.push_back(vertices[2]);
			geom->texcoords.push_back(glm::vec2(deltaWidth * x, deltaDepth * (z + 1)));
			
			// Triangle 2
			geom->vertices.push_back(vertices[0]);
			geom->texcoords.push_back(glm::vec2(deltaWidth * x, deltaDepth * z));
			geom->vertices.push_back(vertices[1]);
			geom->texcoords.push_back(glm::vec2(deltaWidth * (x + 1), deltaDepth * z));
			geom->vertices.push_back(vertices[3]);
			geom->texcoords.push_back(glm::vec2(deltaWidth * (x + 1), deltaDepth * (z + 1)));
						
			for (int j = 0; j < 6; ++j)
			geom->normals.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
		}
	}
	
	initialiseBuffers(geom);
	return geom;
}

//Create serpinski
void divide_sierpinski(geometry* geom, const glm::vec3 vertices[4], int count)
{
	int j; 
	glm::vec3 ab, bc, ac, ad, bd, cd;
	glm::vec3 tempVert[4];
	glm::vec3 tempVert1[4];
	glm::vec3 tempVert2[4];
	glm::vec3 tempVert3[4];

	if(count > 0)
	{
		ab = (vertices[0] + vertices[1])/glm::vec3(2,2,2);
		ac = (vertices[0] + vertices[2])/glm::vec3(2,2,2);         
		ad = (vertices[0] + vertices[3])/glm::vec3(2,2,2);         
		bc = (vertices[1] + vertices[2])/glm::vec3(2,2,2);         
		bd = (vertices[1] + vertices[3])/glm::vec3(2,2,2);         
		cd = (vertices[2] + vertices[3])/glm::vec3(2,2,2);         

		tempVert[0] = vertices[0];
		tempVert[1] = ab;
		tempVert[2] = ac;
		tempVert[3] = ad;
		
		tempVert1[0] = vertices[1];
		tempVert1[1] = ab;
		tempVert1[2] = bc;
		tempVert1[3] = bd;

		tempVert2[0] = vertices[2];
		tempVert2[1] = ac;
		tempVert2[2] = bc;
		tempVert2[3] = cd;

		tempVert3[0] = vertices[3];
		tempVert3[1] = ad;
		tempVert3[2] = bd;
		tempVert3[3] = cd; 

		 divide_sierpinski(geom, tempVert, count-1);
		 divide_sierpinski(geom, tempVert1, count-1);
		 divide_sierpinski(geom, tempVert2, count-1);
		 divide_sierpinski(geom, tempVert3, count-1);		
	}
	else
	{
		for(int i = 0; i < 12; ++i)
		{
				geom->vertices.push_back(vertices[tetrahedron_indices[i]]);
				geom->normals.push_back(glm::normalize(vertices[tetrahedron_indices[i]]));
				geom->texcoords.push_back(tetrahedron_texcoords[i % 3]);
		}
		//for(int i = 0; i < 12; ++i) geom->indices.push_back(tetrahedron_indices[i]);
		//for(int i = 0; i < 12; ++i) tetrahedron_indices[i] = tetrahedron_indices[i] + 4;
	}
	
}

geometry* createSierpinski(int divisions)
{
	glm::vec3 vertices[4];
	std::memcpy(vertices, tetrahedron_vertices, sizeof(glm::vec3) * 4);
	geometry* geom = new geometry();
	divide_sierpinski(geom, vertices, divisions);
	initialiseBuffers(geom);
	//createIndexBuffer(geom);
	return geom;
}



geometry* createVertexBuffer(geometry* geom)
{
	glGenVertexArrays(1, &geom->vao);
	glBindVertexArray(geom->vao);

	glGenBuffers(1, &geom->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geom->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, geom->vertices.size() * sizeof(glm::vec3), &geom->vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//glBindVertexArray(0);

	return geom;
}

geometry* createIndexBuffer(geometry* geom)
{
	glGenBuffers(1, &geom->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geom->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, geom->indices.size() * sizeof(unsigned int), &geom->indices[0],GL_STATIC_DRAW);

	return geom;
}

geometry* createNormalBuffer(geometry* geom)
{
	glGenBuffers(1, &geom->normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geom->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, geom->normals.size() * sizeof(glm::vec3), &geom->normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	return geom;
}

geometry* createTexBuffer(geometry* geom)
{
	glGenBuffers(1, &geom->texcoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geom->texcoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, geom->texcoords.size() * sizeof(glm::vec2), &geom->texcoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	return geom;
}

geometry* createColourBuffer(geometry* geom)
{
	glGenBuffers(1, &geom->colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geom->colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, geom->colours.size() * sizeof(glm::vec4), &geom->colours[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0); // might not be 2 , 2
	glEnableVertexAttribArray(3);

	return geom;
}

void triangle(geometry* geom, const glm::vec3& a, glm::vec3& b, glm::vec3& c)
{
	glm::vec3 normal = glm::normalize(glm::cross(b - a, c - b));

	geom->vertices.push_back(a);
	geom->vertices.push_back(b);
	geom->vertices.push_back(c);

	geom->normals.push_back(a); //makes a smooth sphere
	geom->normals.push_back(b);
	geom->normals.push_back(c);

	for (int i = 0; i < 3; ++i)
		geom->texcoords.push_back(tetrahedron_texcoords[i % 3]);;

	//for (int i = 0; i < 3; ++i) //makes a bumpy sphere
	//	geom->normals.push_back(normal);
}

void divideTriangle(geometry* geom, const glm::vec3& a, glm::vec3& b, glm::vec3& c, int divisions)
{
	if(divisions > 0)
	{
		glm::vec3 ab, ac, bc, abx, acx, bcx;
		glm::vec3 tempA, tempB, tempC;
		glm::vec3 radius = glm::vec3(1.0f, 1.0f, 1.0f);

		ab = glm::normalize(glm::vec3(a + b) / glm::vec3(2.0f, 2.0f, 2.0f));
		ac = glm::normalize(glm::vec3(a + c) / glm::vec3(2.0f, 2.0f, 2.0f));
		bc = glm::normalize(glm::vec3(b + c) / glm::vec3(2.0f, 2.0f, 2.0f));

		
		divideTriangle(geom, a, ab, ac, divisions - 1);
		divideTriangle(geom, ab, b, bc, divisions - 1);
		divideTriangle(geom, ac, bc, c, divisions - 1);
		divideTriangle(geom, ab, ac, bc, divisions - 1);
			
		
	}
	 else triangle(geom, a, b, c);
}

geometry* createSphere(int divisions)
{
	geometry* geom = new geometry();
	glm::vec3 v[4] = 
	{
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.942806, -0.333333),
		glm::vec3(-0.816497, -0.471405, -0.333333),
		glm::vec3(0.816497, -0.471405, -0.333333)
	};

	glm::vec2 t[4] = 
	{
		glm::vec2(v[0].x, v[0].y),
		glm::vec2(v[1].x, v[1].y),
		glm::vec2(v[2].x, v[2].y),
		glm::vec2(v[3].x, v[3].y)
	};
	
	divideTriangle(geom, v[0], v[1], v[2], divisions);
	divideTriangle(geom, v[3], v[2], v[1], divisions);
	divideTriangle(geom, v[0], v[3], v[1], divisions);
	divideTriangle(geom, v[0], v[2], v[3], divisions);

	createVertexBuffer(geom);
	createNormalBuffer(geom);
	createTexBuffer(geom);
	glBindVertexArray(0);
	return geom;
}