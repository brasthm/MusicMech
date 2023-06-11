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
	float t = fract(time + gl_TexCoord[0].x);
	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);
	float dist = distance(gl_TexCoord[0].xy,  vec2(0.5, 0.5));
	vec4 color = clamp(1 - abs(2*(dist) - 5 + 10*(fract(-0.5*time))), 0, 1);

	gl_FragColor = 0.4*color + valImg;
}