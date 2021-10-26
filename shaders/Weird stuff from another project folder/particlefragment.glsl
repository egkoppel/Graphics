#version 330 core
layout(location = 0) out vec4 color;
layout(origin_upper_left) in vec4 gl_FragCoord;
uniform float u_height;
uniform float u_width;
uniform int u_seedx[50];
uniform int u_seedy[50];
uniform float u_seedc[150];
void main(){
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	float maxdistance = sqrt((u_height * u_height) + (u_width * u_width));
	float dist = maxdistance;
	float distancecurrent;
	for(int i = 0; i < 50; i++){\n"
		distancecurrent = sqrt( ( (x - float(u_seedx[i])) * (x - float(u_seedx[i])) ) + ( (y - float(u_seedy[i])) * (y - float(u_seedy[i])) ) );
		if(distancecurrent < dist){
			dist = distancecurrent;
		}
	}
	if(dist < 10){
		color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else{
		color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}