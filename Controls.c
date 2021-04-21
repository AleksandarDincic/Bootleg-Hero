#include <GLFW/glfw3.h>
#include "Controls.h"

short int risingEdge[18] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
short int pressed[10] = { 0,0,0,0,0,0,0,0,0,0 };


void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_Q:
		pressed[0] = 1;
		break;
	case GLFW_KEY_W:
		pressed[1] = 1;
		break;
	case GLFW_KEY_E:
		pressed[2] = 1;
		break;
	case GLFW_KEY_R:
		pressed[3] = 1;
		break;
	case GLFW_KEY_T:
		pressed[4] = 1;
		break;
	case GLFW_KEY_6:
		pressed[5] = 1;
		break;
	case GLFW_KEY_7:
		pressed[6] = 1;
		break;
	case GLFW_KEY_8:
		pressed[7] = 1;
		break;
	case GLFW_KEY_9:
		pressed[8] = 1;
		break;
	case GLFW_KEY_0:
		pressed[9] = 1;
		break;
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_Q:
			pressed[0] = 0;
			break;
		case GLFW_KEY_W:
			pressed[1] = 0;
			break;
		case GLFW_KEY_E:
			pressed[2] = 0;
			break;
		case GLFW_KEY_R:
			pressed[3] = 0;
			break;
		case GLFW_KEY_T:
			pressed[4] = 0;
			break;
		case GLFW_KEY_6:
			pressed[5] = 0;
			break;
		case GLFW_KEY_7:
			pressed[6] = 0;
			break;
		case GLFW_KEY_8:
			pressed[7] = 0;
			break;
		case GLFW_KEY_9:
			pressed[8] = 0;
			break;
		case GLFW_KEY_0:
			pressed[9] = 0;
			break;
		}
	}
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_Q:
			risingEdge[0] = 1;
			break;
		case GLFW_KEY_W:
			risingEdge[1] = 1;
			break;
		case GLFW_KEY_E:
			risingEdge[2] = 1;
			break;
		case GLFW_KEY_R:
			risingEdge[3] = 1;
			break;
		case GLFW_KEY_T:
			risingEdge[4] = 1;
			break;
		case GLFW_KEY_UP:
			risingEdge[5] = 1;
			break;
		case GLFW_KEY_DOWN:
			risingEdge[6] = 1;
			break;
		case GLFW_KEY_LEFT:
			risingEdge[7] = 1;
			break;
		case GLFW_KEY_RIGHT:
			risingEdge[8] = 1;
			break;
		case GLFW_KEY_ENTER:
			risingEdge[9] = 1;
			break;
		case GLFW_KEY_KP_ADD:
			risingEdge[10] = 1;
			break;
		case GLFW_KEY_KP_SUBTRACT:
			risingEdge[11] = 1;
			break;
		case GLFW_KEY_6:
			risingEdge[12] = 1;
			break;
		case GLFW_KEY_7:
			risingEdge[13] = 1;
			break;
		case GLFW_KEY_8:
			risingEdge[14] = 1;
			break;
		case GLFW_KEY_9:
			risingEdge[15] = 1;
			break;
		case GLFW_KEY_0:
			risingEdge[16] = 1;
			break;
		case GLFW_KEY_ESCAPE:
			risingEdge[17] = 1;
			break;
		}
	}
}