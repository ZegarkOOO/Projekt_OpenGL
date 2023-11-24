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
		const char * path,
		std::vector <glm::vec3> & out_vertices,
		std::vector <glm::vec2> & out_uvs,
		std::vector <glm::vec3> & out_normals	)	 
{ 
	//wskazniki vektorow
	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;

	//tymczasowe vektory pozniej beda przekazywane do vektorow z argumentow
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;	
	std::vector <glm::vec3> temp_normals;	
	
	//otwarcie pliku
	
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file!\n");
		return false;
	}
	

	//petla wczytywania lini z pliku dopoki nie bedzie pusty
	while (1) {

		//zakladamy ze linia nie bedzie dluzsza niz 128 znakow
		char lineHeader[128] = "";

		//odczyt kolejnej lini
		int res = fscanf(file, "%s", lineHeader);

		//jesli linia jest pusta przerywamy
		if (res == EOF) {
			break;
		}

		//sprawdzamy pierwszy znak z pliku i porownujemy 
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex; //wierzcholki
			sscanf(lineHeader, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv; //tekstury
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;	//normalne (okreœlaj¹ kierunek powierzchni w danym punkcie i s¹ u¿ywane do obliczeñ oœwietleniowych)
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];	//powierzchnie (definiuja ktore wierzcholki tworza powierzchnie i lacza je z normalnymi i teksturami)
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			
			//sprawdzenie poprawnego wczytania powierzchni
			if (matches != 9) {
				printf("File cant't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}//while
	/*
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

	//to samo c wyzej tylko dla norm
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int vertexIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[vertexIndex - 1];

		//push do naszego vektora z argumentu
		out_normals.push_back(vertex);
	}*/
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}
	fclose(file);
	return true;
}




