#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main()
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load("MyImage.png", &width , &height , &nrChannels, 0);




	for (size_t i = 0; i < 50; i++)
	{
		printf("%d", (int)data[i]);

	}





	return 0;
}