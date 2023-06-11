uniform sampler2D 	source;
uniform float time;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	float t = fract(- 0.2*time + gl_TexCoord[0].x);
	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);

	vec4 color;

	color = vec4(hsv2rgb(vec3(t, 0.8, 0.7)), 1);

	gl_FragColor = color * vec4(1 - valImg.xyz, valImg.w);
}