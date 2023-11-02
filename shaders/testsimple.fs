#version 330 core

in vec2 g_TexCoord;
in vec2 g_LmapCoord;

out vec4 FragColor;

uniform sampler2D s_bspTexture;
uniform sampler2D s_bspLightmap;

void main()
{
FragColor = mix(texture(s_bspTexture, g_TexCoord), texture(s_bspLightmap, g_LmapCoord), 0.5);
}
