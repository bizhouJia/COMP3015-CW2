# CW 2

## Environment

Windows 11 Home Edition

Visual Studio Community 2022 - 17.5.1

glew - 2.1.0

glfw - 3.4

glm - 1.0.1

## Link

https://youtu.be/eXJ1H8SlKRU

## Codes

**initBuffers(&el, &p, &n, nullptr, nullptr);**: 

A call with the vectors of elements (indices), positions (vertices), and normals, along with two `nullptr` placeholders for additional data (not used here). This function is responsible for setting up the necessary OpenGL buffers and configurations to render the cup based on the calculated vertices, normals, and indices.

vector<GLfloat> p;

A vector to store the vertices of the cup. Each vertex consists of a position in 3D space.

vector<GLuint> el;

A vector to store the indices for elements (triangles) that make up the surface of the cup. These indices refer to vertices in the `p` vector.

vector<GLfloat> n;

A vector to store normals for each vertex. Normals are used in lighting calculations to determine how light interacts with the surface.

Cup::Cup(float topRadius, float bottomRadius, float height, unsigned int segments): 

The constructor for the Cup class, initializing a cup object with specific top and bottom radii, height, and the number of segments for the circular parts.

GLuint texID = Texture::loadTexture("/media/texture/glass.jpg");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

This sequence of commands is typical for preparing a texture for use in rendering in an OpenGL application.

This presumably calls a custom function `loadTexture()` from a class or namespace named `Texture`, which loads an image file located at `/media/texture/glass.jpg` into memory and creates a texture object in OpenGL. The function returns a texture ID (`texID`), which uniquely identifies the texture in the OpenGL context.

OpenGL supports multiple texture units, which allow you to use more than one texture in shaders simultaneously. `glActiveTexture()` sets the active texture unit, and `GL_TEXTURE0` is the first texture unit. This line ensures that subsequent texture operations affect the first texture unit.

This function binds the texture object identified by `texID` to the target texture type, which is `GL_TEXTURE_2D` in this case. Binding a texture makes it the current texture for the active texture unit, and it will be used by subsequent OpenGL operations that involve a 2D texture.

layout (binding = 0) uniform sampler2D Tex1;

layout (binding = 0): This part of the declaration specifies the binding point of the uniform variable. Binding points are used to establish a connection between the shader program and the OpenGL application. By setting `binding = 0`, you are specifying that this sampler should be linked to the texture unit 0. This should match the texture unit activated in your application code with `glActiveTexture(GL_TEXTURE0);`.

uniform: This keyword declares that `Tex1` is a uniform variable. Uniforms are a type of GLSL variable that are used to pass data from your application on the CPU to the shaders running on the GPU. They maintain their values across the execution of the shader program for multiple vertices or fragments.

sampler2D: This specifies the type of the uniform variable `Tex1`. In this case, it's a 2D texture sampler, which means that `Tex1` can be used within the shader to access the texture data (color, depth, etc.) from a 2D texture bound to the specified texture unit (in this case, unit 0).

Tex1: This is the name of the uniform variable as it will be used within the shader to sample the texture.