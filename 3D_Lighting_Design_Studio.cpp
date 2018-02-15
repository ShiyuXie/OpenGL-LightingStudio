// 3D_Lighting_Design_Studio.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "3D_Lighting_Design_Studio.h"

void mySpecialKey(int key, int x, int y) {
	if (light[lightnum] != NULL){
		GLfloat moveY = light[lightnum]->position[2];
		GLfloat temp = 0;
		GLfloat tempF = 0;

		switch (key)
		{
		case GLUT_KEY_DOWN:

			moveY = moveY - 10.0;
			break;

		case GLUT_KEY_UP:

			moveY = moveY + 10.0;
			break;

		}

		temp = moveY;
		if (temp < -290)
		{
			temp = -290;
		}
		else if (temp > 290)
		{
			temp = 290;
		}

		light[lightnum]->changeZ(temp);

		glutPostRedisplay();
	}
}

void selectFont(int size, int charset, const char* face) //Internet
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void drawString(const char* str) //draw characters on screen
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}

void changeOnMenu(){

	glutSetMenu(turnOn);
	int temp = glutGet(GLUT_MENU_NUM_ITEMS);
	for (int i = temp; i >= 1; i--){
		glutRemoveMenuItem(i);
	}
	if (light[0] != NULL &&  light[0]->state == true){
		glutAddMenuEntry("Light1", 1);
	}
	if (light[1] != NULL&& light[1]->state == true){
		glutAddMenuEntry("Light2", 2);
	}
	if (light[2] != NULL&& light[2]->state == true){
		glutAddMenuEntry("Light3", 3);
	}
	if (light[3] != NULL&& light[3]->state == true){
		glutAddMenuEntry("Light4", 4);
	}
	if (light[4] != NULL&& light[4]->state == true){
		glutAddMenuEntry("Light5", 5);
	}
	if (light[5] != NULL&& light[5]->state == true){
		glutAddMenuEntry("Light6", 6);
	}
}

void changeDelMenu(){
	glutSetMenu(delLight);
	int temp = glutGet(GLUT_MENU_NUM_ITEMS);
	for (int i = temp; i >= 1; i--){
		glutRemoveMenuItem(i);
	}
	if (light[0] != NULL){
		glutAddMenuEntry("Light1", 1);
	}
	if (light[1] != NULL){
		glutAddMenuEntry("Light2", 2);
	}
	if (light[2] != NULL){
		glutAddMenuEntry("Light3", 3);
	}
	if (light[3] != NULL){
		glutAddMenuEntry("Light4", 4);
	}
	if (light[4] != NULL){
		glutAddMenuEntry("Light5", 5);
	}
	if (light[5] != NULL){
		glutAddMenuEntry("Light6", 6);
	}
}

void changeOffMenu(){
	glutSetMenu(turnOff);
	int temp = glutGet(GLUT_MENU_NUM_ITEMS);
	for (int i = temp; i >= 1; i--){
		glutRemoveMenuItem(i);
	}
	if (light[0] != NULL&&  light[0]->state == false){
		glutAddMenuEntry("Light1", 1);
	}
	if (light[1] != NULL&&  light[1]->state == false){
		glutAddMenuEntry("Light2", 2);
	}
	if (light[2] != NULL&&  light[2]->state == false){
		glutAddMenuEntry("Light3", 3);
	}
	if (light[3] != NULL&&  light[3]->state == false){
		glutAddMenuEntry("Light4", 4);
	}
	if (light[4] != NULL&&  light[4]->state == false){
		glutAddMenuEntry("Light5", 5);
	}
	if (light[5] != NULL&&  light[5]->state == false){
		glutAddMenuEntry("Light6", 6);
	}
}

void changeMyMenu(){
	glutSetMenu(menu);

	if (light[0] == NULL && light[1] == NULL&& light[2] == NULL&& light[3] == NULL&& light[4] == NULL&& light[5] == NULL){
		glutChangeToMenuEntry(current, "Current Light: None", current);
	}
	else if (light[0] == NULL && lightnum == 0){
		glutChangeToMenuEntry(current, "Current Light: None", current);
	}
	else if (lightnum + 1 == LIGa){
		glutChangeToMenuEntry(current, "Current Light: Light1", current);
	}
	else if (lightnum + 1 == LIGb){
		glutChangeToMenuEntry(current, "Current Light: Light2", current);
	}
	else if (lightnum + 1 == LIGc){
		glutChangeToMenuEntry(current, "Current Light: Light3", current);
	}
	else if (lightnum + 1 == LIGd){
		glutChangeToMenuEntry(current, "Current Light: Light4", current);
	}
	else if (lightnum + 1 == LIGe){
		glutChangeToMenuEntry(current, "Current Light: Light5", current);
	}
	else if (lightnum + 1 == LIGf){
		glutChangeToMenuEntry(current, "Current Light: Light6", current);
	}
}

void turnOffSub(int data)
{
	int i = data - 1;
	printf("turn off is working\n");
	if (light[i] != NULL){
		glDisable(GL_LIGHT0 + i);
		light[i]->state = true;
		light[i]->light_color[2].lighting[0] = 0.0;
		light[i]->light_color[2].lighting[1] = 0.0;
		light[i]->light_color[2].lighting[2] = 0.0;

		light[i]->light_color[1].lighting[0] = 0.0;
		light[i]->light_color[1].lighting[1] = 0.0;
		light[i]->light_color[1].lighting[2] = 0.0;

		light[i]->light_color[0].lighting[0] = 0.0;
		light[i]->light_color[0].lighting[1] = 0.0;
		light[i]->light_color[0].lighting[2] = 0.0;
		lightnum = 0;
		//return;
		printf("i is %d\n", i);
	}
	changeOffMenu();
	changeOnMenu();
	changeDelMenu();
	changeMyMenu();

}

void turnOnSub(int data)
{
	int i = data - 1;
	if (light[i] != NULL && light[i]->state == true){
		glEnable(GL_LIGHT0 + i);
		light[i]->light_color[2].lighting[0] = 1.0;
		light[i]->light_color[2].lighting[1] = 1.0;
		light[i]->light_color[2].lighting[2] = 1.0;

		light[i]->light_color[1].lighting[0] = 1.0;
		light[i]->light_color[1].lighting[1] = 1.0;
		light[i]->light_color[1].lighting[2] = 1.0;

		light[i]->light_color[0].lighting[0] = 0.0;
		light[i]->light_color[0].lighting[1] = 0.0;
		light[i]->light_color[0].lighting[2] = 0.0;
		lightnum = 0;
		light[i]->state = false;
	}
	changeOffMenu();
	changeOnMenu();
	changeDelMenu();
	changeMyMenu();

}

/*此处用NULL暂时替代了finalizer的效果，实际会在内存里留下不可清除的部分。finalizer用于在对象消亡时，清空内存。*/
void delLightSub(int data)
{
	int i = data - 1;
	if (light[i] != NULL){
		light[i] = NULL;
		glDisable(GL_LIGHT0 + i);
		lightnum = 0;
	}
	changeOffMenu();
	changeOnMenu();
	changeDelMenu();
	changeMyMenu();
}

void menuFunc(int data){
	changeOffMenu();
	changeOnMenu();
	changeDelMenu();
	changeMyMenu();
}

void myMenu(){
	glutPushWindow();

	turnOff = glutCreateMenu(turnOffSub);

	turnOn = glutCreateMenu(turnOnSub);

	delLight = glutCreateMenu(delLightSub);

	menu = glutCreateMenu(menuFunc);

	glutAddMenuEntry("Current Light: None", menu);
	glutAddSubMenu("Turn off", turnOff);
	glutAddSubMenu("Turn on", turnOn);
	glutAddSubMenu("Delete a light", delLight);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutPopWindow();
}

void lines(){
	glPushMatrix();
	glTranslatef(180, 230, -200);//Angle
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 200, -200);//Attenu
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 365, -200);//x
	glScalef(170, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(220, 365, -200);
	glRotatef(180, 0, 0, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 365, -200);//y
	glRotatef(90, 0, 0, 1);
	glScalef(170, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(140, 445, -200);
	glRotatef(-90, 0, 0, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(145, 370, -200);//z
	glRotatef(45, 0, 0, 1);
	glScalef(185, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(210, 435, -200);
	glRotatef(-135, 0, 0, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 560, -200);//lr
	//glRotatef(90, 0, 0, 1);
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 530, -200);//lg
	//glRotatef(90, 0, 0, 1);
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 500, -200);//lb
	//glRotatef(90, 0, 0, 1);
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 145, -200);//or
	//glRotatef(90, 0, 0, 1);
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 115, -200);//og
	//glRotatef(90, 0, 0, 1);
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 85, -200);//ob
	//glRotatef(90, 0, 0, 1);
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 50, -200);//Shiness
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(570, 50, -200);//Scale
	glScalef(130, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(142, 642, -200);//column1
	glRotatef(180, 0, 0, 1);
	glScalef(257, 1.5, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(204, 619, -200);//column1.5
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(142, 580, -200);//column2
	glRotatef(180, 0, 0, 1);
	glScalef(257, 1.5, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(105, 555, -200);//column2.1
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(260, 555, -200);//column2.2
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(105, 505, -200);//column2.3
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(260, 505, -200);//column2.4
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(142, 465, -200);//column3
	glRotatef(180, 0, 0, 1);
	glScalef(257, 1.5, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(142, 250, -200);//column4
	glRotatef(180, 0, 0, 1);
	glScalef(257, 1.5, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(142, 165, -200);//column5
	glRotatef(180, 0, 0, 1);
	glScalef(257, 1.5, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(105, 140, -200);//column5.1
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(260, 140, -200);//column5.2
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(105, 90, -200);//column5.3
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(260, 90, -200);//column5.4
	glRotatef(90, 0, 0, 1);
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(825, 50, -200);//column6
	glRotatef(90, 0, 0, 1);
	glScalef(85, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	

	glPushMatrix();
	glTranslatef(1025, 50, -200);//column7
	glRotatef(90, 0, 0, 1);
	glScalef(85, 1, 0);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(495, 50, 0);
	glScalef(10, 2, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(648, 50, 0);
	glScalef(10, 2, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(648, 50, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(10, 2, 0);
	glutSolidCube(1);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[6]);
	glPushMatrix();
	glTranslatef(357, 50, 0);
	glLoadName(PREV);
	arrow3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(771, 50, 0);
	glRotatef(180, 0, 0, 1);
	glLoadName(NEXT);
	arrow3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(43, 620, 0);//pointlight
	glLoadName(CREATE);
	point();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(90, 628, 0);//spotlight
	glLoadName(OFF);
	spot();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(166, 610, 0);//distant
	glLoadName(MODIFY);
	distant();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(240, 620, 0);//global
	glLoadName(GLOBAL);
	globalLight();
	glPopMatrix();
}

void signs(){
	selectFont(16, ANSI_CHARSET, "Times New Roman");

	glRasterPos2i(890, 700 - 690);
	drawString("Pause/Resume");
	glRasterPos2i(1082, 700 - 669);
	drawString("1");
	glRasterPos2i(1122, 700 - 669);
	drawString("2");
	glRasterPos2i(1162, 700 - 669);
	drawString("3");
	glRasterPos2i(250, 700 - 32);
	drawString("?");

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	if (openHint==true){
		glRasterPos2i(290, 700 - 15);
		drawString("                         ***********Hints**********");
		glRasterPos2i(290, 700 - 35);
		drawString("1.Use Special Key Up and Down to change object position on Z axis.");
		glRasterPos2i(290, 700 - 55);
		drawString("2.Click the right button of mouse to turn off, turn on or delete a light.");
		glRasterPos2i(290, 700 - 75);
		drawString("3.The light source type from left to right are point source, spotlight,");
		glRasterPos2i(290, 700 - 95);
		drawString("  distant light and global ambient light.");
		glRasterPos2i(290, 700 - 115);
		drawString("4.You can only turn off or turn on the global ambient light.");
		glRasterPos2i(290, 700 - 135);
		drawString("5.The light source with a cross on it is the current selected light.");
		glRasterPos2i(290, 700 - 155);
		drawString("                ***Click the button again to close the hints***");
	}
	glRasterPos2i(29, 700 - 145);
	drawString("Ambient");
	
	glRasterPos2i(29, 700 - 175);
	drawString("Specular");
	glRasterPos2i(100, 700 - 175);
	drawString("0");
	glRasterPos2i(250, 700 - 175);
	drawString("255");

	glRasterPos2i(29, 700 - 205);
	drawString("Diffuse");

	glRasterPos2i(29, 700 - 559);
	drawString("Ambient");
	glRasterPos2i(29, 700 - 579);
	drawString("Specular");

	glRasterPos2i(100, 700 - 589);
	drawString("0");
	glRasterPos2i(250, 700 -589);
	drawString("255");

	glRasterPos2i(29, 700 - 599);
	drawString("Diffuse");
	glRasterPos2i(29, 700 - 619);
	drawString("Emission");
	
	glRasterPos2i(126, 700 - 270);
	drawString("Y");

	glRasterPos2i(205, 700 - 280);
	drawString("Z");
	
	glRasterPos2i(210, 700 - 350);
	drawString("X");

	glRasterPos2i(65, 700 - 32);
	drawString("LIGHT & MATERIALS");
	glRasterPos2i(20, 700 - 52);
	drawString("Light Source");
	glRasterPos2i(20, 700 - 115);
	drawString("Light Color");
	glRasterPos2i(20, 700 - 230);
	drawString("Spotlight & Distant light Only");
	glRasterPos2i(29, 700 - 255);
	drawString("Direction:");
	glRasterPos2i(20, 700 - 445);
	drawString("Spotlight Only");
	glRasterPos2i(29, 700 - 475);
	drawString("Angle: ");
	glRasterPos2i(100, 700 - 475);
	drawString("0");
	glRasterPos2i(250, 700 - 475);
	drawString("90");
	glRasterPos2i(29, 700 - 505);
	drawString("Attenuation:");
	glRasterPos2i(100, 700 - 505);
	drawString("0");
	glRasterPos2i(250, 700 - 505);
	drawString("100");
	glRasterPos2i(20, 700 - 530);
	drawString("Material Color");
	glRasterPos2i(29, 700 - 655);
	drawString("Shininess:");
	glRasterPos2i(100, 700 - 655);
	drawString("0");
	glRasterPos2i(250, 700 - 655);
	drawString("100");
	
	glRasterPos2i(330, 700 - 610);
	drawString("OBJECT SIZE & TYPE");
	
	glRasterPos2i(850, 700 - 610);
	drawString("ANIMATION");

	glRasterPos2i(865, 700 - 639);
	drawString("Rotate");
	glRasterPos2i(940, 700 - 639);
	drawString("Translate");

	glRasterPos2i(865, 700 - 663);
	drawString("X axis");
	glRasterPos2i(920, 700 - 663);
	drawString("Y axis");
	glRasterPos2i(975, 700 - 663);
	drawString("Z axis");

	glRasterPos2i(1040, 700 - 610);
	drawString("CODE GENERATION");
	glRasterPos2i(1040, 700 - 669);
	drawString("Files:");


	/*glRasterPos2i(170, 700 - 580);
	drawString("Use Key Up and Down");
	glRasterPos2i(170, 700 - 600);
	drawString("to move a light on Z axis");*/
	glRasterPos2i(1055, 700 - 640);
	drawString("Save");
	glRasterPos2i(1140, 700 - 640);
	drawString("Load");

}

void buttonRender(){
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(NEXT);
	pBtnNext.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(PREV);
	pBtnPrevious.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(CREATE);
	pBtnPoint.Render();
	

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(OFF);
	pBtnSpot.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(MODIFY);
	pBtnDistant.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(GLOBAL);
	pBtnGlobal.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(LABN);
	pBtnAmbL.Render();

	glLoadName(LSPE);
	pBtnSpeL.Render();

	glLoadName(LDIF);
	pBtnDifL.Render();
	
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(SAVE);
	pBtnSave.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(LOAD);
	pBtnLoad.Render();

	glLoadName(ROTATE);
	pBtnRotate.Render();

	glLoadName(TRANSLATE);
	pBtnTranslate.Render();

	glLoadName(OXA);
	pBtnOxa.Render();

	glLoadName(OYA);
	pBtnOya.Render();

	glLoadName(OZA);
	pBtnOza.Render();

	glLoadName(OABN);
	pBtnAmbO.Render();

	glLoadName(OSPE);
	pBtnSpeO.Render();

	glLoadName(ODIF);
	pBtnDifO.Render();

	glLoadName(OEMI);
	pBtnEmiO.Render();

	glLoadName(HINT);
	pBtnHint.Render();
	
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(ANI);
	pBtnAnimation.Render();
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(FILEI);
	pBtnFile1.Render();

	glLoadName(FILEII);
	pBtnFile2.Render();

	glLoadName(FILEIII);
	pBtnFile3.Render();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[5]);
	glPushMatrix();
	glTranslatef(attenu_pos[0], attenu_pos[1], 0);
	glLoadName(ATTENA);
	pSldAttenu.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(angle_pos[0], angle_pos[1], 0);
	glLoadName(ANGLE);
	pSldAngle.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(lx_pos[0], lx_pos[1], 0);
	glLoadName(LXA);
	pSldLx.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ly_pos[0], ly_pos[1], 0);
	glLoadName(LYA);
	pSldLy.Render();
	glPopMatrix();

	glPushMatrix();
	glLoadName(LZA);
	glTranslatef(lz_pos[0], lz_pos[1], 0);
	glRotatef(45, 0, 0, 1);
	pSldLz.Render();
	glPopMatrix();

	glPushMatrix();
	glLoadName(OSHIN);
	glTranslatef(shin_pos[0], shin_pos[1], 0);
	pSldShin.Render();
	glPopMatrix();

	glPushMatrix();
	glLoadName(OSCALE);
	glTranslatef(scale_pos[0], scale_pos[1], 0);
	pSldScale.Render();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[1]);
	glPushMatrix();
	glLoadName(SLDRL);
	glTranslatef(lr_pos[0], lr_pos[1], 0);
	pSldLr.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(or_pos[0], or_pos[1], 0);
	glLoadName(SLDRO);
	pSldOr.Render();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[2]);
	glPushMatrix();
	glTranslatef(lg_pos[0], lg_pos[1], 0);
	glLoadName(SLDGL);
	pSldLg.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(og_pos[0], og_pos[1], 0);
	glLoadName(SLDGO);
	pSldOg.Render();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[3]);
	glPushMatrix();
	glTranslatef(lb_pos[0], lb_pos[1], 0);
	glLoadName(SLDBL);
	pSldLb.Render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ob_pos[0], ob_pos[1], 0);
	glLoadName(SLDBO);
	pSldOb.Render();
	glPopMatrix();

	glPopMatrix();
}

void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);

	glEnable(GL_LIGHTING);

	//changeMyMenu();

	float model_ambient[] = { 0.5f*global, 0.5f*global, 0.5f*global, 1.0f };

	glViewport(0, 0, 1200, 700);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, no_emission);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_emission);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
	signs();

	glInitNames();
	glPushName(0);
	buttonRender();

	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
	glLoadName(OBJECT);
	lines();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, Materials.material_color[0].materials);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Materials.material_color[1].materials);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Materials.material_color[2].materials);
	glMaterialfv(GL_FRONT, GL_SHININESS, &Materials.shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, Materials.material_color[3].materials);
	glTranslatef(670, 370, 0);

	glViewport(280, 120, 920, 580);
	switch (nextObject) {
	case 1:
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){
			
		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);
			
		}
		glPushMatrix();
		glScalef(3 * Materials.scale, 3 * Materials.scale, 3 * Materials.scale);
		DNA();

		glPopMatrix();
		break;
	case 2:
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}
		glScalef(4.2*Materials.scale, 4.2*Materials.scale, 4.2*Materials.scale);
		helicopter();
		break;
	case 3:
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}
		glScalef(4.2*Materials.scale, 4.2*Materials.scale, 4.2*Materials.scale);
		castle();
		break;
	case 4:
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}

		glScalef(4.2*Materials.scale, 4.2*Materials.scale, 4.2*Materials.scale);
		goat();
		break;
	case 5:
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}

		glScalef(0.9*Materials.scale, 0.9*Materials.scale, 0.9*Materials.scale);
		wheel();
		break;
	case 6:
		glScalef(1.1*Materials.scale, 1.1*Materials.scale, 1.1*Materials.scale);
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef((CAS/4)*axiS[0], (CAS/8)*axiS[1], CAS*axiS[2]);

		}
		aCube();
		break;
	case 7:
		glPushMatrix();
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[0], axis[1], axis[2]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}
		glScalef(1.7*Materials.scale, 1.7*Materials.scale, 1.7*Materials.scale);
		castle();
		glPopMatrix();

		glPushMatrix();
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[2], axis[1], axis[0]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}
		
		glTranslatef(0, 180, 0);
		glScalef(1.7*Materials.scale, 1.7*Materials.scale, 1.7*Materials.scale);
		helicopter();
		glPopMatrix();

		glPushMatrix();
		if (axis[0] == 0 && axis[1] == 0 && axis[2] == 0){

		}
		else {
			glRotatef(theta[DN], axis[1], axis[2], axis[0]);
		}
		if (axiS[0] == 0 && axiS[1] == 0 && axiS[2] == 0){

		}
		else {
			glTranslatef(CAS*axiS[0], CAS*axiS[1], CAS*axiS[2]);

		}

		glTranslatef(180,0,0);
		glScalef(1.7*Materials.scale, 1.7*Materials.scale, 1.7*Materials.scale);
		goat();
		glPopMatrix();
		break;
	}
	glPopMatrix();

	/*for (int i=0; i < 6; i++){
	if (id == LIGa + i){
	if (light[i] != NULL){
	glPushMatrix();
	light[i]->sign();
	printf("Iamworking\n");
	glPopMatrix();
	return;
	}
	}
	}*/

	/*	glPushMatrix();
	//glTranslatef(600, 390, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, no_emission);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_emission);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

	glTranslatef(600, 640, 280);
	glRotatef(45, 0, 0, 1);
	glScalef(8, 2, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(600, 640, 280);
	glRotatef(-45, 0, 0, 1);
	glScalef(8, 2, 1);
	glutSolidCube(1);
	glPopMatrix();*/

	


	//highLight = id - 1;


	//myMenu();
	//changeOffMenu();
	//changeOnMenu();
	//changeDelMenu();
	//changeMyMenu();
	glViewport(0, 0, 1200, 700);
	for (int i = 0; i < 6; i++){
		if (light[i] != NULL){
			glPushMatrix();
			glLoadName(LIGa + i);
			light[i]->shape();
			light[i]->properties(i);
			glPopMatrix();
		}

		if (lightnum == i){
			if (light[i] != NULL){
				glPushMatrix();
				light[i]->sign();

				glPopMatrix();
				//return;
			}
		}
	}

	glutSwapBuffers();
}


void myInit(void) {
	//glClearColor(0.8,0.8,0.8,1.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	//glEnable(GL_CULL_FACE);
	pBtnHint = Question();
	pBtnHint.m_fPosX = 235;
	pBtnHint.m_fPosY = 653;
	pBtnHint.m_fWidth = 40;
	pBtnHint.m_fHeight = 40;

	pBtnPoint = CreatePoint();
	pBtnPoint.m_fPosX = -10;
	pBtnPoint.m_fPosY = 590;
	pBtnPoint.m_fWidth = 105;
	pBtnPoint.m_fHeight = 60;

	pBtnSpot = CreateSpot();
	pBtnSpot.m_fPosX = 52;
	pBtnSpot.m_fPosY = 590;
	pBtnSpot.m_fWidth = 105;
	pBtnSpot.m_fHeight = 60;

	pBtnDistant = CreateDistant();
	pBtnDistant.m_fPosX = 114;
	pBtnDistant.m_fPosY = 590;
	pBtnDistant.m_fWidth = 105;
	pBtnDistant.m_fHeight = 60;

	pBtnGlobal = Global();
	pBtnGlobal.m_fPosX = 187;
	pBtnGlobal.m_fPosY = 590;
	pBtnGlobal.m_fWidth = 105;
	pBtnGlobal.m_fHeight = 60;

	pBtnAmbL = RadioButton();
	pBtnAmbL.m_fPosX = 17;
	pBtnAmbL.m_fPosY = 555;
	pBtnAmbL.m_fWidth = 10;
	pBtnAmbL.m_fHeight = 10;

	pBtnSpeL = RadioButton();
	pBtnSpeL.m_fPosX = 17;
	pBtnSpeL.m_fPosY = 525;
	pBtnSpeL.m_fWidth = 10;
	pBtnSpeL.m_fHeight = 10;

	pBtnDifL = RadioButton();
	pBtnDifL.m_fPosX = 17;
	pBtnDifL.m_fPosY = 495;
	pBtnDifL.m_fWidth = 10;
	pBtnDifL.m_fHeight = 10;

	pBtnAmbO = MaterialRadio();
	pBtnAmbO.m_fPosX = 17;
	pBtnAmbO.m_fPosY = 140;
	pBtnAmbO.m_fWidth = 10;
	pBtnAmbO.m_fHeight = 10;

	pBtnSpeO = MaterialRadio();
	pBtnSpeO.m_fPosX = 17;
	pBtnSpeO.m_fPosY = 120;
	pBtnSpeO.m_fWidth = 10;
	pBtnSpeO.m_fHeight = 10;

	pBtnDifO = MaterialRadio();
	pBtnDifO.m_fPosX = 17;
	pBtnDifO.m_fPosY = 100;
	pBtnDifO.m_fWidth = 10;
	pBtnDifO.m_fHeight = 10;

	pBtnEmiO = MaterialRadio();
	pBtnEmiO.m_fPosX = 17;
	pBtnEmiO.m_fPosY = 80;
	pBtnEmiO.m_fWidth = 10;
	pBtnEmiO.m_fHeight = 10;

	pSldLr = Slider();
	pSldLr.m_fPosX = 0;
	pSldLr.m_fPosY = -10;
	pSldLr.m_fWidth = 20;
	pSldLr.m_fHeight = 40;

	pSldLg = Slider();
	pSldLg.m_fPosX = 0;
	pSldLg.m_fPosY = -10;
	pSldLg.m_fWidth = 20;
	pSldLg.m_fHeight = 40;

	pSldLb = Slider();
	pSldLb.m_fPosX = 0;
	pSldLb.m_fPosY = -10;
	pSldLb.m_fWidth = 20;
	pSldLb.m_fHeight = 40;

	pSldAttenu = Slider();
	pSldAttenu.m_fPosX = -10;
	pSldAttenu.m_fPosY = 0;
	pSldAttenu.m_fWidth = 20;
	pSldAttenu.m_fHeight = 40;

	pSldAngle = Slider();
	pSldAngle.m_fPosX = -10;
	pSldAngle.m_fPosY = 0;
	pSldAngle.m_fWidth = 20;
	pSldAngle.m_fHeight = 40;

	pSldLx = Slider();
	pSldLx.m_fPosX = -10;
	pSldLx.m_fPosY = 0;
	pSldLx.m_fWidth = 20;
	pSldLx.m_fHeight = 40;

	pSldLy = Slider();
	pSldLy.m_fPosX = 0;
	pSldLy.m_fPosY = -10;
	pSldLy.m_fWidth = 40;
	pSldLy.m_fHeight = 20;

	pSldLz = Slider();
	pSldLz.m_fPosX = 0;
	pSldLz.m_fPosY = 0;
	pSldLz.m_fWidth = 20;
	pSldLz.m_fHeight = 40;

	pBtnSave = CodeRadio();
	pBtnSave.m_fPosX = 1042;
	pBtnSave.m_fPosY = 60;
	pBtnSave.m_fWidth = 10;
	pBtnSave.m_fHeight = 10;

	pBtnLoad = CodeRadio();
	pBtnLoad.m_fPosX = 1127;
	pBtnLoad.m_fPosY = 60;
	pBtnLoad.m_fWidth = 10;
	pBtnLoad.m_fHeight = 10;

	pBtnRotate = ObjectRadio();
	pBtnRotate.m_fPosX = 852;
	pBtnRotate.m_fPosY = 60;
	pBtnRotate.m_fWidth = 10;
	pBtnRotate.m_fHeight = 10;

	pBtnTranslate = ObjectRadio();
	pBtnTranslate.m_fPosX = 928;
	pBtnTranslate.m_fPosY = 60;
	pBtnTranslate.m_fWidth = 10;
	pBtnTranslate.m_fHeight = 10;

	pBtnOxa = CheckButton();
	pBtnOxa.m_fPosX = 847;
	pBtnOxa.m_fPosY = 30;
	pBtnOxa.m_fWidth = 20;
	pBtnOxa.m_fHeight = 20;

	pBtnOya = CheckButton();
	pBtnOya.m_fPosX = 904;
	pBtnOya.m_fPosY = 30;
	pBtnOya.m_fWidth = 20;
	pBtnOya.m_fHeight = 20;

	pBtnOza = CheckButton();
	pBtnOza.m_fPosX = 958;
	pBtnOza.m_fPosY = 30;
	pBtnOza.m_fWidth = 20;
	pBtnOza.m_fHeight = 20;

	pBtnFile1 = Files1();
	pBtnFile1.m_fPosX = 1065;
	pBtnFile1.m_fPosY = 15;
	pBtnFile1.m_fHeight = 40;
	pBtnFile1.m_fWidth = 40;

	pBtnFile2 = Files2();
	pBtnFile2.m_fPosX = 1105;
	pBtnFile2.m_fPosY = 15;
	pBtnFile2.m_fHeight = 40;
	pBtnFile2.m_fWidth = 40;

	pBtnFile3 = Files3();
	pBtnFile3.m_fPosX = 1145;
	pBtnFile3.m_fPosY = 15;
	pBtnFile3.m_fHeight = 40;
	pBtnFile3.m_fWidth = 40;

	pSldOg = Slider();
	pSldOg.m_fPosX = 0;
	pSldOg.m_fPosY = -10;
	pSldOg.m_fWidth = 20;
	pSldOg.m_fHeight = 40;

	pSldOb = Slider();
	pSldOb.m_fPosX = 0;
	pSldOb.m_fPosY = -10;
	pSldOb.m_fWidth = 20;
	pSldOb.m_fHeight = 40;

	pSldOr = Slider();
	pSldOr.m_fPosX = 0;
	pSldOr.m_fPosY = -10;
	pSldOr.m_fWidth = 20;
	pSldOr.m_fHeight = 40;

	pSldShin = Slider();
	pSldShin.m_fPosX = -10;
	pSldShin.m_fPosY = 0;
	pSldShin.m_fWidth = 20;
	pSldShin.m_fHeight = 40;

	pSldScale = Slider();
	pSldScale.m_fPosX = -10;
	pSldScale.m_fPosY = 0;
	pSldScale.m_fWidth = 20;
	pSldScale.m_fHeight = 40;

	pBtnAnimation = Animation();
	pBtnAnimation.m_fPosX = 847;
	pBtnAnimation.m_fPosY = -4;
	pBtnAnimation.m_fWidth = 170;
	pBtnAnimation.m_fHeight = 35;

	pBtnNext = Next();
	pBtnNext.m_fPosX = 750;
	pBtnNext.m_fPosY = 25;
	pBtnNext.m_fWidth = 50;
	pBtnNext.m_fHeight = 50;

	pBtnPrevious = Previous();
	pBtnPrevious.m_fPosX = 330;
	pBtnPrevious.m_fPosY = 25;
	pBtnPrevious.m_fWidth = 50;
	pBtnPrevious.m_fHeight = 50;
}

void ProcessSelection(int xPos, int yPos)
{
	GLfloat fAspect;

	static GLuint selectBuff[BUFFER_LENGTH];

	GLint hits, viewport[4];

	glSelectBuffer(BUFFER_LENGTH, selectBuff);

	glGetIntegerv(GL_VIEWPORT, viewport);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glRenderMode(GL_SELECT);

	glLoadIdentity();
	gluPickMatrix(xPos, viewport[3] - yPos, 2, 2, viewport);

	//glViewport(0, 0, 1200, 700);
	glOrtho(-0, 1200, -0, 700, -300, 300);

	mydisplay();

	hits = glRenderMode(GL_RENDER);

	if (hits > 0)
	{
		int Choose = selectBuff[3];
		int depth = selectBuff[1];

		for (int loop = 1; loop<hits; loop++)
		{
			if (selectBuff[loop * 4 + 1] < GLuint(depth))
			{
				Choose = selectBuff[loop * 4 + 3];
				depth = selectBuff[loop * 4 + 1];
			}
		}
		id = Choose;
		printf("id is %d\n", id);
	}
	mydisplay();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

class GVector{
public:
	GLdouble posx;
	GLdouble posy;
	GLdouble posz;

	GVector(GLdouble x, GLdouble y, GLdouble z){
		posx = x;
		posy = y;
		posz = z;
	};
};

GVector screen2world(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	GVector v(posX, posY, posZ);
	return v;
}

GVector vec(0, 0, 0);

void mouse(int button, int state, int x, int y)
{
	glutPostRedisplay();
	if (button == GLUT_RIGHT_BUTTON){
		glutPostRedisplay();
	}
	else if (button == GLUT_LEFT_BUTTON)
		switch (state)
	{
		case GLUT_DOWN:

			ProcessSelection(x, y);
			if (id < CREATE){
				if (id>0){
					lightnum = id - 1;
				}
				if (light[lightnum] != NULL)
				{
					light[lightnum]->changePosition();

				}
				glutPostRedisplay();
			}
			else if (id<ANGLE && id!=LOAD)
			{
				pBtn[id - 7]->OnMouseDown(x, y);
				
				glutPostRedisplay();
			}
			else if (id == LOAD){
				pBtn[id - 7]->OnMouseDown(x, y);
				Materials.changePosition();
				if (light[0] != NULL){
					light[0]->changePosition();
				}
				glutPostRedisplay();
			}
			else if (id == HINT){
				openHint = !openHint;
			}
			else {

			}

			if (ligcolornum == 0){
				pBtnAmbL.select = true;
				pBtnSpeL.select = false;
				pBtnDifL.select = false;
			}
			else if (ligcolornum == 1){
				pBtnSpeL.select = true;
				pBtnAmbL.select = false;
				pBtnDifL.select = false;
			}
			else if (ligcolornum == 2){
				pBtnDifL.select = true;
				pBtnAmbL.select = false;
				pBtnSpeL.select = false;
			}

			if (colornum == 0){
				pBtnAmbO.select = true;
				pBtnSpeO.select = false;
				pBtnDifO.select = false;
				pBtnEmiO.select = false;
			}
			else if (colornum == 1){
				pBtnSpeO.select = true;
				pBtnAmbO.select = false;
				pBtnDifO.select = false;
				pBtnEmiO.select = false;
			}
			else if (colornum == 2){
				pBtnDifO.select = true;
				pBtnAmbO.select = false;
				pBtnSpeO.select = false;
				pBtnEmiO.select = false;
			}
			else if (colornum == 3){
				pBtnDifO.select = false;
				pBtnAmbO.select = false;
				pBtnSpeO.select = false;
				pBtnEmiO.select = true;
			}

			if (codenum == 1){
				pBtnSave.select = true;
				pBtnLoad.select = false;
			}
			else if (codenum == 2){
				pBtnSave.select = false;
				pBtnLoad.select = true;
			}

			if (objectnum == 1){
				pBtnRotate.select = true;
				pBtnTranslate.select = false;
			}
			else if (objectnum == 2){
				pBtnRotate.select = false;
				pBtnTranslate.select = true;
			}

			break;
		case GLUT_UP:
			if (id<CREATE)
			{
				id = -1;
			}
			else if (id<LABN){
				pBtn[id - 7]->OnMouseUp();
				id = -1;
			}
			else if (id<GLOBAL){

			}
			else if (id < OABN){
				pBtn[id - 7]->OnMouseUp();
				id = -1;
			}
			else if (id<ANI){

			}
			else if (id<ANGLE){
				pBtn[id - 7]->OnMouseUp();
				id = -1;
			}
			else{
				id = -1;
			}
			break;
	}
	changeOffMenu();
	changeOnMenu();
	changeDelMenu();
	changeMyMenu();
}

void MouseMoveCallback(int x, int y)
{
	glutPostRedisplay();
	GLint viewport[4];
	GLfloat fA;
	GLint temp;
	GLfloat tempF;

	glGetIntegerv(GL_VIEWPORT, viewport);
	fA = (float)viewport[2] / (float)viewport[3];//width<height
	vec = screen2world(x, y);
	//cout << lightnum << endl;

	for (int i = 0; i < 6; i++){
		if (id == LIGa + i){
			if (light[i] != NULL){
				if (POINT == light[i]->type() || SPOT == light[i]->type()){
					light[i]->position[0] = (float)vec.posx;
					light[i]->position[1] = (float)vec.posy;
					glutPostRedisplay();
					return;
				}
			}
		}
	}//*/

	if (id == SLDRL)
	{
		temp = (float)vec.posx;
		if (temp < 110)
		{
			temp = 110;
		}
		else if (temp > 230){
			temp = 230;
		}
		if (light[lightnum] != NULL){
			lr_pos[0] = temp;
			tempF = (GLfloat)lr_pos[0];
			light[lightnum]->light_color[ligcolornum].lighting[0] = ((tempF - 110.0) / 120.0) * 1.0;
		}
		mydisplay();
	}
	else if (id == SLDGL)
	{
		temp = (float)vec.posx;
		if (temp < 110)
		{
			temp = 110;
		}
		else if (temp > 230){
			temp = 230;
		}
		if (light[lightnum] != NULL){
			lg_pos[0] = temp;
			tempF = (GLfloat)lg_pos[0];
			light[lightnum]->light_color[ligcolornum].lighting[1] = ((tempF - 110.0) / 120.0) * 1.0;
		}
		mydisplay();
	}
	else if (id == SLDBL)
	{
		temp = (float)vec.posx;
		if (temp < 110)
		{
			temp = 110;
		}
		else if (temp > 230){
			temp = 230;
		}
		if (light[lightnum] != NULL){
			lb_pos[0] = temp;
			tempF = (GLfloat)lb_pos[0];
			light[lightnum]->light_color[ligcolornum].lighting[2] = ((tempF - 110.0) / 120.0) * 1.0;
		}
		printf("x is %f\n",lb_pos[0]);
		mydisplay();
	}
	else if (id == ANGLE)
	{
		temp = (float)vec.posx;
		if (temp < 120)
		{
			temp = 120;
		}
		else if (temp > 245){
			temp = 245;
		}
		if (light[lightnum] != NULL&&light[lightnum]->type() == SPOT){
			angle_pos[0] = temp;
			tempF = (GLfloat)angle_pos[0];
			light[lightnum]->changeAngle(((tempF - 120.0) / 125.0) * 90.0);
		}
		mydisplay();
	}
	else if (id == ATTENA)
	{
		temp = (float)vec.posx;
		if (temp < 120)
		{
			temp = 120;
		}
		else if (temp > 245){
			temp = 245;
		}
		if (light[lightnum] != NULL&&light[lightnum]->type() == SPOT){
			attenu_pos[0] = temp;
			tempF = (GLfloat)attenu_pos[0];
			light[lightnum]->changeAttenu(((tempF - 120.0) / 125.0) * 100.0);
		}
		mydisplay();
	}
	else if (id == LXA)
	{
		temp = (float)vec.posx;
		if (temp < 60)
		{
			temp = 60;
		}
		else if (temp > 230){
			temp = 230;
		}
		if (light[lightnum] != NULL && light[lightnum]->type() != POINT){
			lx_pos[0] = temp;
			tempF = (GLfloat)lx_pos[0];
			light[lightnum]->changeDirection(-1.0 + ((tempF - 60.0) / 170.0) * 2.0, 0);
			if (DISTANT == light[lightnum]->type()){
				light[lightnum]->position[0] = 665 + 330 * light[lightnum]->direction[0];
			}
		}
		mydisplay();
	}
	else if (id == LYA)
	{
		temp = (float)vec.posy;
		if (temp < 280)
		{
			temp = 280;
		}
		else if (temp > 450){
			temp = 450;
		}
		if (light[lightnum] != NULL && light[lightnum]->type() != POINT){
			ly_pos[1] = temp;
			tempF = (GLfloat)ly_pos[1];
			light[lightnum]->changeDirection(-1.0 + ((tempF - 280.0) / 170.0) * 2.0, 1);
			if (DISTANT == light[lightnum]->type()){
				light[lightnum]->position[1] = 350 + 300 * light[lightnum]->direction[1];
			}
		}
		mydisplay();
	}
	else if (id == LZA)
	{
		temp = (float)vec.posx;

		if (temp < 90)
		{
			temp = 90;

		}
		else if (temp > 218){
			temp = 218;

		}

		if (light[lightnum] != NULL&&light[lightnum]->type()!=POINT){
			lz_pos[0] = temp;
			lz_pos[1] = 195 + temp;
			light[lightnum]->changeDirection(-1.0f + ((temp - 90.0f) / 128.0f) * 2.0f, 2);
			if (DISTANT == light[lightnum]->type()){
				if (light[lightnum]->direction[2] > 0){
					light[lightnum]->position[2] = -70 + 300 * light[lightnum]->direction[2];
				}
				else{
					light[lightnum]->position[2] = 300 * light[lightnum]->direction[2];
				}
			}
		}
		mydisplay();
	}
	else if (id == SLDRO)
	{
		temp = (float)vec.posx;
		if (temp < 110)
		{
			temp =	110;
		}
		else if (temp > 230){
			temp = 230;
		}
		or_pos[0] = temp;
		tempF = (GLfloat)or_pos[0];
		Materials.material_color[colornum].materials[0] = ((tempF - 110.0) / 120.0) * 1.0;
		mydisplay();
	}
	else if (id == SLDGO)
	{
		temp = (float)vec.posx;
		if (temp < 110)
		{
			temp = 110;
		}
		else if (temp > 230){
			temp = 230;
		}
		og_pos[0] = temp;
		tempF = (GLfloat)og_pos[0];
		Materials.material_color[colornum].materials[1] = ((tempF - 110.0) / 120.0) * 1.0;
		mydisplay();
	}
	else if (id == SLDBO)
	{
		temp = (float)vec.posx;
		if (temp < 110)
		{
			temp = 110;
		}
		else if (temp > 230){
			temp = 230;
		}
		ob_pos[0] = temp;
		tempF = (GLfloat)ob_pos[0];
		Materials.material_color[colornum].materials[2] = ((tempF - 110.0) / 120.0) * 1.0;
		mydisplay();
	}
	else if (id == OSHIN)
	{
		temp = (float)vec.posx;
		if (temp < 120)
		{
			temp = 120;
		}
		else if (temp > 245){
			temp = 245;
		}
		shin_pos[0] = temp;
		tempF = (GLfloat)shin_pos[0];
		Materials.changeShin(((tempF - 120.0) / 125.0) * 100.0);
		mydisplay();
	}
	else if (id == OSCALE)
	{
		temp = (float)vec.posx;
		if (temp < 510)
		{
			temp = 510;
		}
		else if (temp > 635){
			temp = 635;
		}
		scale_pos[0] = temp;
		tempF = (GLfloat)scale_pos[0];
		Materials.changeScale(((tempF - 510.0) / 125.0) * 49+1);
		mydisplay();
	}
}

void idle() {
	glutPostRedisplay();
	
	if (pause)
		return;
	if (dna) {
		theta[DN] += 0.08;
		if (theta[LIGa] > 360) theta[LIGa] -= 360;
	}
	if (heli) {
		theta[HELI] += 0.1;
		if (theta[LIGa] > 360) theta[LIGa] -= 360;
	}
	/*if (cas) {
		if (cas_direction > 0){
			CAS += 1;
			if (CAS > 100) {
				cas_direction = -1;
				CAS -= 1;
			}
			else {
				CAS -= 1;
				if (CAS < -100){
					cas_direction = 1;
					CAS += 1;
				}
			}		
		}
	}*/
	if (cas) {
		if (cas_direction == 1){
			CAS = CAS + 0.5;
			if (CAS > 300)
			{
				cas_direction = -1;
				CAS -= 0.5;
			}
		}
		else {
			CAS -= 0.5;
			if (CAS < -300)
			{
				cas_direction = 1;
				CAS += 0.5;
			}
		}

	}
	//printf("CAS value is %f\n", CAS);
	//printf("DNA value is %f\n",theta[DN]);
}

void reshape(int w, int h) {
	GLfloat aspectRatio;

	if (h == 0)
		h = 1;
	glViewport(0, 0, 1200, 700);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	glOrtho(-0.0, 1200.0, -0.0, 700.0, -300.0, 300.0);
	/*if (w <= h) {
	glOrtho(-0.0, 1200.0, -0.0 * aspectRatio, 700.0 * aspectRatio, -100.0, 100.0);
	}
	else{
	glOrtho(-0.0 * aspectRatio, 1200.0 *aspectRatio, -0.0, 700.0, -100.0, 100.0);
	}*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutCreateWindow("3D Lighting Design Studio");
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	//
	glutMotionFunc(MouseMoveCallback);
	glutSpecialFunc(mySpecialKey);
	glutReshapeFunc(reshape);
	glutDisplayFunc(mydisplay);
	myInit();
	myMenu();
	glutMainLoop();
}

