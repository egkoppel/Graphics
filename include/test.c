#ifdef _cplusplus
extern "C" {
#endif

void oninit(){}
void ondest(){}
float clearcolor[4] = { 0.0f, 0.3f, 0.2f, 0.0f };
void onupdate(float deltatime){}

void onrender() {
	glClearColor(clearcolor[0], clearcolor[1], clearcolor[2], clearcolor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void onimguirender() {
	ImGui::ColorEdit4("Clear Colour", clearcolor);
}

#ifdef _cplusplus
}
#endif