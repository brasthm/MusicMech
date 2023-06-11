uniform sampler2D 	source;
uniform float time;

#define TAU 6.283185

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float invlerp(float a, float b, float v) {
	return (v-a)/(b-a);
}

void main()
{
	float x = gl_TexCoord[0].x;
	float t = 10 * time;


	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);

	float a = 0.05 * cos (6.6 * x * TAU + 0.8123 - t);
	float b = 0.05 * cos (2.2 * x * TAU + 0.173423 - t);
	float c = 0.05 * cos (3.7 * x * TAU + 1.99345 - t);
	float d = 0.05 * cos (4.1 * x * TAU + 233.2542 - t);
	float e = 0.05 * cos (7.2 * x * TAU + 12.75 - t);
	float f = 0.05 * cos (3.65 * x * TAU + 2.534 - t);
	float g = 0.05 * cos (4.2 * x * TAU + 98.1 - t);

	float courbe = a + b + c + d + e + f + g + 0.5;

	float dist = (1 - distance(gl_TexCoord[0].xy, vec2(x, courbe)));

	float glow = clamp(invlerp(0.8, 1, dist), 0, 1);
	float line = dist > 0.99;


	vec3 color = line * vec3(1, 1, 1) + (1-line) * glow * vec3(hsv2rgb(vec3(0.15, 0.6, 1)));



	gl_FragColor = vec4(color, 1) + valImg;
}