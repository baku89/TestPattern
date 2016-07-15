uniform vec3 color1;
uniform vec3 color2;

void main() {
	vec2 pos = gl_FragCoord.xy - vec2(0.5);

	vec3 color = mix(color1, color2, 1.0 - clamp(mod(pos.x, 4.0) + mod(pos.y, 4.0), 0.0, 1.0));

	gl_FragColor = vec4(color, 1.0);
}