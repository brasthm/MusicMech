uniform sampler2D 	source;
uniform float time;

#define TAU 6.283185

void main()
{



	// transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
gl_Position.x  = gl_Position.x + 0.2*gl_Position.y * cos(time);
    

    // forward the vertex color
    gl_FrontColor = gl_Color;
}