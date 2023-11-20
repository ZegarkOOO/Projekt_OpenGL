#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

//GLEW
#include <glew.h>

//GLFW
#include <glfw3.h>

//OpenGL Math libs
#include <glm.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



bool loadOBJ(
	std::string path,
	std::vector <glm::vec3>& out_vertices,
	std::vector <glm::vec2>& out_uvs,
	std::vector <glm::vec3>& out_normals)
{
	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;

	//tymczasowe vektory pozniej beda przekazywane do vektorow z argumentow
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;
	std::vector <glm::vec3> temp_normals;


	std::stringstream ss;
	std::ifstream infile(path);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	unsigned int temp_glint = 0;

	if (!infile.is_open()) {
		std::cout << "could not open file " << path << std::endl;
		throw "ERROR";
	}
	while (std::getline(infile, line)) {
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "#") {}
		else if (prefix == "o") {}
		else if (prefix == "s") {}
		else if (prefix == "use_mtl") {}
		else if (prefix == "v") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			temp_vertices.push_back(temp_vec3);
		}
		else if (prefix == "vt") {
			ss >> temp_vec2.x >> temp_vec2.y;
			temp_uvs.push_back(temp_vec2);
		}
		else if (prefix == "vn") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			temp_normals.push_back(temp_vec3);
		}
		else if (prefix == "f") {
			int counter = 0;
			while (ss >> temp_glint) {
				if (counter == 0) {
					vertexIndices.push_back(temp_glint);
				}
				else if (counter == 1) {
					uvIndices.push_back(temp_glint);
				}
				else if (counter == 2) {
					normalIndices.push_back(temp_glint);
				}

				if (ss.peek() == '/') {
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ') {
					++counter;
					ss.ignore(1, ' ');
				}

				if (counter > 1) {
					counter = 0;
				}
			}//while
		}
		else {}

		//petla przypisujemy dane z temp_vertices do vec3 (vektor ktorego lubi OpenGL)
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];

			//push do naszego vektora z argumentu
			out_vertices.push_back(vertex);
		}

		//to samo co wyzej tylko dla tekstur
		for (unsigned int i = 0; i < uvIndices.size(); i++) {
			unsigned int vertexIndex = uvIndices[i];
			glm::vec2 vertex = temp_uvs[vertexIndex - 1];

			//push do naszego vektora z argumentu
			out_uvs.push_back(vertex);
		}

		//to samo co wyzej tylko dla norm
		for (unsigned int i = 0; i < normalIndices.size(); i++) {
			unsigned int vertexIndex = normalIndices[i];
			glm::vec3 vertex = temp_normals[vertexIndex - 1];

			//push do naszego vektora z argumentu
			out_normals.push_back(vertex);
		}
	}
}