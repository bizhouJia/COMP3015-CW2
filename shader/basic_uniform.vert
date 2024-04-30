#version 460

// Input vertex attributess
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

// Output to the fragment shader
// The computed intensity of the light at the vertexs
out vec3 LightIntensity;

// Uniform variables - shared across all vertices and set by the CPU
// The position of the light in eye coordinates
uniform vec4 LightPosition;

// The diffuse reflectivity of the material
uniform vec3 Kd;

// The diffuse light intensity
uniform vec3 Ld;

// Matrices for transforming vertices and normals
// Transforms model coordinates to eye coordinates
uniform mat4 ModelViewMatrix;

// Transforms normals to eye coordinates
uniform mat3 NormalMatrix;

// ModelViewProjection matrix for transforming to clip coordinates
uniform mat4 MVP;

void main()
{
    // Normalize the transformed normal to account for non-uniform scaling
    vec3 n = normalize(NormalMatrix * VertexNormal);

    // Transform the vertex position to eye coordinates
    vec4 pos = ModelViewMatrix * vec4(VertexPosition, 1.0);

    // Calculate the direction from this vertex to the light source
    vec3 s = normalize(vec3(LightPosition - pos));

    // Calculate the dot product of the light vector and the normal vector,
    // clamped to the range [0,1]
    float sDotN = max(dot(s,n), 0.0);

    // Calculate the diffuse component of the light reflected by the vertex
    vec3 diffuse = Ld * Kd * sDotN;

    // Pass the calculated light intensity to the fragment shader
    LightIntensity = diffuse;

    // Calculate the clip space position of the vertex for rasterization
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
