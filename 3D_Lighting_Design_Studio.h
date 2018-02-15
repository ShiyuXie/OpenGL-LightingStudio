#define MAX_CHAR 128  
#define MAX 7
#define MIN 1

#define DN 0
#define HELI 1
#define CA 2
#define SHE 3

#define LIGa 1
#define LIGb 2
#define LIGc 3
#define LIGd 4
#define LIGe 5
#define LIGf 6

#define CREATE 7
#define OFF 8
#define MODIFY 9
#define LABN 10
#define LSPE 11
#define LDIF 12
#define GLOBAL 13
#define SAVE 14
#define LOAD 15
#define NEXT 16
#define PREV 17
#define OABN 18
#define OSPE 19
#define ODIF 20
#define OEMI 21
#define ANI 22

#define ROTATE 23
#define TRANSLATE 24
#define OXA 25
#define OYA 26
#define OZA 27

#define FILEI 28
#define FILEII 29
#define FILEIII 30

#define ANGLE 31
#define ATTENA 32
#define SLDRL 33
#define SLDGL 34
#define SLDBL 35
#define LXA 36
#define LYA 37
#define LZA 38
#define SLDRO 39
#define SLDGO 40
#define SLDBO 41
#define OSHIN 42
#define OSCALE 43
#define HINT 44

#define OBJECT 45
#define LINES 46

#define POINT		1
#define SPOT		2
#define DISTANT		3

#define BUFFER_LENGTH 64

float CAS = 0.0;

int lightnum = 0;
int ligcolornum = -1;
int colornum = 0;
int id;
int highLight = 0;
int current = 1;
int codenum = 0;
int objectnum = 0;
int axisnum = 0;
int axisnum2 = 0;

int axis[3] = { 0, 0, 0 };
int axiS[3] = { 0, 0, 0 };
GLfloat global = 1.0;
GLfloat theta[3] = { 0.0, 0.0, 0.0 };

GLboolean dna = GL_TRUE;
GLboolean heli = GL_TRUE;
GLboolean cas = GL_TRUE;
GLboolean pause = GL_FALSE;
GLboolean openHint = GL_FALSE;
//GLboolean select = GL_FALSE;

GLint cas_direction = 1;

float mat_emission[7][4] = { { 0.8f, 0.8f, 0.8f, 1.0f }, { 1.0, 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0, 1.0 }, { 0.4, 0.4, 0.4, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }, {0.0,0.0,0.0,1.0} };
float no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lr_pos[4] = { 110.0, 550.0, 10.0, 1.0 };
GLfloat lg_pos[4] = { 110.0, 520.0, 10.0, 1.0 };
GLfloat lb_pos[4] = { 110.0, 490.0, 10.0, 1.0 };
GLfloat angle_pos[4] = { 120, 210.0, 10.0, 1.0 };
GLfloat attenu_pos[4] = { 120.0, 180.0, 10.0, 1.0 };
GLfloat or_pos[4] = { 110.0, 135.0, 10.0, 1.0 };
GLfloat og_pos[4] = { 110.0, 105.0, 10.0, 1.0 };
GLfloat ob_pos[4] = { 110.0, 75.0, 10.0, 1.0 };
GLfloat shin_pos[4] = { 170.0, 30.0, 10.0, 1.0 };
GLfloat scale_pos[4] = {535.0,30.0,10.0,1.0};
GLfloat lx_pos[4] = { 60,345.0, 10.0, 1.0 };
GLfloat ly_pos[4] = { 120.0, 280, 10.0, 1.0 };
GLfloat lz_pos[4] = { 95.0, 290.0, 10.0, 1.0 };

int nextObject = MIN;

GLUquadricObj *obj;

float g_fWidth = 1200;
float g_fHeight = 700;
float g_fDepth = 200;
float g_fAngle = 0.0;

int menu, turnOff, turnOn, delLight;

//menu
void changeOffMenu();
void changeOnMenu();
void changeDelMenu();

class LightingStruct {
public:
	GLfloat lighting[4];
};

class materialStruct {
public:
	GLfloat materials[4];
};

class Material{
public:
	GLfloat load, loadpos;
	GLfloat sload, sloadpos;
	GLfloat shininess;
	GLfloat scale;
	materialStruct material_color[4];

	Material(){
		material_color[0].materials[0] = 0.5;
		material_color[0].materials[1] = 0.2;
		material_color[0].materials[2] = 0.2;
		material_color[0].materials[3] = 1.0;

		material_color[1].materials[0] = 1.0;
		material_color[1].materials[1] = 1.0;
		material_color[1].materials[2] = 1.0;
		material_color[1].materials[3] = 1.0;

		material_color[2].materials[0] = 1.0;
		material_color[2].materials[1] = 0.0;
		material_color[2].materials[2] = 0.0;
		material_color[2].materials[3] = 1.0;

		material_color[3].materials[0] = 0.0;
		material_color[3].materials[1] = 0.0;
		material_color[3].materials[2] = 0.0;
		material_color[3].materials[3] = 1.0;

		shininess = 40;

		scale = 10;
	}

	void changeShin(GLfloat parameter){
		shininess = parameter;
	}
	void changeScale(GLfloat parameter){
		scale = parameter;
	}
	void changePosition(){
		load = shininess;
		loadpos = (load /100.0) * 125.0 + 125.0;
		shin_pos[0] = loadpos;

		sload = scale;
		sloadpos = (sload / 100.0) * 125.0 + 510.0;
		scale_pos[0] = sloadpos;
	}
};

Material Materials;


class PointLight{
public:
	LightingStruct light_color[3];
	GLfloat position[4];
	GLfloat angle;
	GLfloat attenu;
	GLfloat direction[4];

	GLfloat dx, dxpos;
	GLfloat dy, dypos;
	GLfloat dz, dzpos;
	GLfloat keyz, keyzpos;

	bool state = false;

	PointLight(){
		light_color[0].lighting[0] = 0.0;
		light_color[0].lighting[1] = 0.0;
		light_color[0].lighting[2] = 0.0;
		light_color[0].lighting[3] = 1.0;

		light_color[1].lighting[0] = 1.0;
		light_color[1].lighting[1] = 1.0;
		light_color[1].lighting[2] = 1.0;
		light_color[1].lighting[3] = 1.0;

		light_color[2].lighting[0] = 1.0;
		light_color[2].lighting[1] = 1.0;
		light_color[2].lighting[2] = 1.0;
		light_color[2].lighting[3] = 1.0;

		position[0] = 600.0 + 30 * lightnum;
		position[1] = 350.0 + 290.0;
		position[2] = 270.0;
		position[3] = 1.0;

		direction[0] = 0.0;
		direction[1] = -1.0;
		direction[2] = -1.0;
		direction[3] = 1.0;

		angle = 180.0;
		attenu = 0.0;
	};

	virtual void shape(){
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_emission);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, no_emission);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_emission);
		glMaterialfv(GL_FRONT, GL_SHININESS, &no_emission[0]);
		glMaterialfv(GL_FRONT, GL_EMISSION, light_color[2].lighting);
		glTranslatef(position[0], position[1], position[2]);
		glutSolidSphere(6.5, 20, 20);
		glPopMatrix();
	}

	virtual void sign(){
		glPushMatrix();
		//printf("Iamworking%d\n",lightnum);
		//glTranslatef(600, 390, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_emission);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, no_emission);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_emission);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

		glTranslatef(position[0], position[1], position[2] + 10);
		glRotatef(45, 0, 0, 1);
		glScalef(8, 1.5, 1);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(position[0], position[1], position[2] + 10);
		glRotatef(-45, 0, 0, 1);
		glScalef(8, 1.5, 1);
		glutSolidCube(1);
		glPopMatrix();
	}

	virtual void properties(int num){
		glLightfv(GL_LIGHT0 + num, GL_AMBIENT, light_color[0].lighting);
		glLightfv(GL_LIGHT0 + num, GL_SPECULAR, light_color[1].lighting);
		glLightfv(GL_LIGHT0 + num, GL_DIFFUSE, light_color[2].lighting);
		glLightfv(GL_LIGHT0 + num, GL_POSITION, position);
	}

	virtual void changeDirection(GLfloat parameter, int axis){
		printf("Invalid operation:(\n");
	}

	virtual void changeAttenu(GLfloat parameter)
	{
		printf("Invalid operation:(\n");
	}

	virtual void changeAngle(GLfloat paremeter)
	{
		printf("Invalid operation:(\n");
	}

	virtual void changePosition()
	{

	}

	virtual void changeZ(GLfloat parameter){
		position[2] = parameter;
	}

	virtual int type(){
		return POINT;
	}
};

class DistantLight : public PointLight{
public:

	DistantLight(){
		direction[0] = 0.5;
		direction[1] = -0.5;
		direction[2] = 0.5;
		direction[3] = 0.0;
	};

	void properties(int num)
	{
		glLightfv(GL_LIGHT0 + num, GL_AMBIENT, light_color[0].lighting);
		glLightfv(GL_LIGHT0 + num, GL_SPECULAR, light_color[1].lighting);
		glLightfv(GL_LIGHT0 + num, GL_DIFFUSE, light_color[2].lighting);
		glLightfv(GL_LIGHT0 + num, GL_POSITION, direction);
	}

	void shape(){
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_emission);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, no_emission);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_emission);
		glMaterialfv(GL_FRONT, GL_SHININESS, &no_emission[0]);
		glMaterialfv(GL_FRONT, GL_EMISSION, light_color[2].lighting);
		glTranslatef(position[0], position[1], position[2]);
		//glTranslatef(665+330 *direction[0], 350+300 *direction[1], -300 + 300 * abs(direction[2]));
		glutSolidCube(10);
		glPopMatrix();
	}

	void changeDirection(GLfloat parameter, int axis){
		direction[axis] = parameter;

	}

	void changePosition()
	{
		dx = direction[0];
		dxpos = (dx + 1.0) * 85.0 + 60.0;
		lx_pos[0] = dxpos;

		dy = direction[1];
		dypos = (dy + 1.0) * 85.0 + 280.0;
		ly_pos[1] = dypos;

		dz = direction[2];
		dzpos = (dz + 1.0) * 64.0 + 90.0;
		lz_pos[0] = dzpos;
		lz_pos[1] = dzpos + 195;

	}
	int type(){
		return DISTANT;
	}
};

class SpotLight : public PointLight{
public:
	GLfloat an, anpos;
	GLfloat at, atpos;

	SpotLight(){
		angle = 30.0;
	};

	void shape(){
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_emission);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, no_emission);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_emission);
		glMaterialfv(GL_FRONT, GL_SHININESS, &no_emission[0]);
		glMaterialfv(GL_FRONT, GL_EMISSION, light_color[2].lighting);
		glTranslatef(position[0], position[1], position[2]);
		glutSolidSphere(8, 20, 20);
		glPopMatrix();
	}

	void properties(int num){
		glLightfv(GL_LIGHT0 + num, GL_AMBIENT, light_color[0].lighting);
		glLightfv(GL_LIGHT0 + num, GL_SPECULAR, light_color[1].lighting);
		glLightfv(GL_LIGHT0 + num, GL_DIFFUSE, light_color[2].lighting);
		glLightfv(GL_LIGHT0 + num, GL_POSITION, position);
		glLightfv(GL_LIGHT0 + num, GL_SPOT_CUTOFF, &angle);
		glLightfv(GL_LIGHT0 + num, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT0 + num, GL_SPOT_EXPONENT, &attenu);
	}

	void changeAngle(GLfloat parameter){
		angle = parameter;
	}

	void changeAttenu(GLfloat parameter){
		attenu = parameter;
	}

	void changeDirection(GLfloat parameter, int axis){
		direction[axis] = parameter;
	}

	void changePosition(){
		dx = direction[0];
		dxpos = (dx + 1.0) * 85.0 + 60.0;
		lx_pos[0] = dxpos;

		dy = direction[1];
		dypos = (dy + 1.0) * 85.0 + 280.0;
		ly_pos[1] = dypos;

		dz = direction[2];
		dzpos = (dz + 1.0) *60.0 + 90.0;
		lz_pos[0] = dzpos;
		lz_pos[1] = dzpos + 195;

		an = angle;
		anpos = (an / 90.0)*125.0 + 120.0;
		angle_pos[0] = anpos;

		at = attenu;
		atpos = (at / 100.0) * 125.0 + 120;
		attenu_pos[0] = atpos;
	}

	int type(){
		return SPOT;
	}
};

PointLight *light[6] = { NULL };

class Button
{
public:
	float m_fPosX;		//表示在正交投影坐标系(左下角为坐标原点)的坐标，
	float m_fPosY;
	float m_fWidth;		//屏幕像素单位
	float m_fHeight;
	bool press = false;

	Button(){};
	virtual void Render()
	{
		glPushMatrix();
		{

			glTranslatef(m_fPosX + m_fWidth / 2, m_fPosY + m_fHeight / 2, -2.0);
			if (press == true){
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[0]);
				//glScalef(0.9,0.9,1);
			}
			glScalef(0.5*m_fWidth, 0.5*m_fHeight, 0.5*5.0);
			glutSolidCube(1.0);
		}
		glPopMatrix();
	}
	virtual void OnMouseDown(int mousex, int mousey)
	{
		//press = !press;
		press = true;

	}
	virtual void OnMouseUp()
	{
		//press = !press;
		press = false;
		//glScalef(0.9, 0.9, 1);
	}
};

class CheckButton:public Button{
public:
	bool cSelect = false;

	virtual void Render(){
		glPushMatrix();
		{

			glTranslatef(m_fPosX + m_fWidth / 2, m_fPosY + m_fHeight / 2, -2.0);
			if (press == true){

			}
			if (cSelect){
				glPushMatrix();
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[0]);
				//glScalef(0.9,0.9,0.9);
				glScalef(0.6*0.5*m_fWidth, 0.6*0.5*m_fHeight, 5*0.5*5.0);
				
				glutSolidCube(1.0);
				glPopMatrix();
			}
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
			glScalef(0.5*m_fWidth, 0.5*m_fHeight, 0.5*5.0);
			glutWireCube(1.0);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[6]);
			glutSolidCube(1.0);
		}
		glPopMatrix();
	}
	virtual void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		//cSelect = !cSelect;
		if (objectnum == 1){
			
			axisnum = id - 25;
			if (axis[axisnum] == 0){
				axis[axisnum] = 1;
				cSelect = true;
			}
			else if (axis[axisnum] == 1){
				axis[axisnum] = 0;
				cSelect = false;
			}
		}
		else if (objectnum == 2){
			printf("objectnum is %d\n", objectnum);
			axisnum2 = id - 25;
			if (axiS[axisnum2] == 0){
				axiS[axisnum2] = 1;
				cSelect = true;
			}
			else if (axiS[axisnum2] == 1){
				axiS[axisnum2] = 0;
				cSelect = false;
			}
			printf("array number is %d\n", axiS[axisnum2]);
		}
	}

};

class RadioButton :public Button{
public:
	bool select = false;

	virtual void Render(){
		glPushMatrix();
		{
			glTranslatef(m_fPosX + m_fWidth / 2, m_fPosY + m_fHeight / 2, -2.0);
			if (press == true){

			}
			if (select){
				glPushMatrix();
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[0]);
				//glScalef(0.9,0.9,0.9);
				glScalef(0.85*0.5*m_fWidth, 0.85*0.5*m_fHeight, 5.5*0.5*5.0);

				glutSolidSphere(1.0,20,20);
				glPopMatrix();
			}
			glPushMatrix();
			glScalef(0.95*0.5*m_fWidth, 0.95*0.5*m_fHeight, 5.0*0.5*5.0);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[6]);
			glutSolidSphere(1.0,20,20);
			glPopMatrix();
			
			glPushMatrix();
			glScalef(0.5*m_fWidth, 0.5*m_fHeight, 0.5*5.0);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[4]);
			glutSolidSphere(1.2,20,20);
			glPopMatrix();
		}
		glPopMatrix();
	}
	virtual void OnMouseDown(int mousex, int mousey){

		ligcolornum = id - 10;
		GLfloat red;
		GLfloat redpos;

		GLfloat green;
		GLfloat greenpos;

		GLfloat blue;
		GLfloat bluepos;


		if (light[lightnum] != NULL)
		{
			red = (GLfloat)(light[lightnum]->light_color[id - 10]).lighting[0];
			redpos = red * 120 + 110;
			lr_pos[0] = redpos;

			green = light[lightnum]->light_color[id - 10].lighting[1];
			greenpos = green * 120 + 110;
			lg_pos[0] = greenpos;

			blue = light[lightnum]->light_color[id - 10].lighting[2];
			bluepos = blue * 120 + 110;
			lb_pos[0] = bluepos;
		}
		else
		{
			printf("Invalid operation:(\n");
		}
	}
	
};

class CodeRadio :public RadioButton{
	void OnMouseDown(int mousex, int mousey){
		codenum = id - 13;
		printf("code number is %d\n", codenum);
	}
};
CheckButton pBtnOxa;
CheckButton pBtnOya;
CheckButton pBtnOza;
class ObjectRadio :public RadioButton{
	void OnMouseDown(int mousex, int mousey){
		objectnum = id - 22;
		if (objectnum == 1){
			if (axis[0] == 1){
				pBtnOxa.cSelect = true;
			}
			else if (axis[0] == 0){
				pBtnOxa.cSelect = false;
			}

			if (axis[1] == 1){
				pBtnOya.cSelect = true;
			}
			else if (axis[1] == 0){
				pBtnOya.cSelect = false;
			}
			if (axis[2] == 1){
				pBtnOza.cSelect = true;
			}
			else if (axis[2] == 0){
				pBtnOza.cSelect = false;
			}
		}

		else if (objectnum == 2){
			if (axiS[0] == 1){
				pBtnOxa.cSelect = true;
			}
			else if (axiS[0] == 0){
				pBtnOxa.cSelect = false;
			}


			if (axiS[1] == 1){
				pBtnOya.cSelect = true;
			}
			else if (axiS[1] == 0){
				pBtnOya.cSelect = false;
			}
			if (axiS[2] == 1){
				pBtnOza.cSelect = true;
			}
			else if (axiS[2] == 0){
				pBtnOza.cSelect = false;
			}
		}

		

		

		printf("code number is %d\n", codenum);
	}
};

class MaterialRadio : public RadioButton{
	void OnMouseDown(int mousex, int mousey){

		colornum = id - 18;
		GLfloat red = Materials.material_color[colornum].materials[0];
		GLfloat redpos = red * 120 + 110;
		or_pos[0] = redpos;

		GLfloat green = Materials.material_color[colornum].materials[1];
		GLfloat greenpos = green * 120 + 110;
		og_pos[0] = greenpos;

		GLfloat blue = Materials.material_color[colornum].materials[2];
		GLfloat bluepos = blue * 120 + 110;
		ob_pos[0] = bluepos;
	}
};

class Animation : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		//press = !press;
		press = true;
		pause = !pause;
	}
};

class Next : public Button{
public:

	void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		nextObject++;
		if (nextObject > MAX)
		{
			nextObject = MIN;
		}
	}
};

class Previous : public Button{
public:

	void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		nextObject--;
		if (nextObject < MIN) nextObject = MAX;
	}
};

class CreateSpot : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		bool flag = false;
		for (int i = 0; i < 6; i++)
		{
			if (light[i] == NULL)
			{
				lightnum = i;
				glEnable(GL_LIGHT0 + i);

				glPushMatrix();
				light[i] = new SpotLight();
				light[i]->properties(i);
				glPopMatrix();
				lightnum = 0;
				ligcolornum = 0;
				flag = true;
				break;
			}
		}
		if (flag == false){
			printf("Sorry, the system only allows 6 light sources:(\n");
		}
	}
};

class CreatePoint : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		bool flag = false;
		for (int i = 0; i < 6; i++)
		{
			if (light[i] == NULL)
			{
				lightnum = i;
				glEnable(GL_LIGHT0 + i);

				glPushMatrix();
				light[i] = new PointLight();
				light[i]->properties(i);
				glPopMatrix();
				lightnum = 0;
				ligcolornum = 0;
				flag = true;
				break;
			}

		}
		if (flag == false){
			printf("Sorry, the system only allows 6 light sources:(\n");
		}
	}
};

class CreateDistant : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		bool flag = false;
		for (int i = 0; i < 6; i++)
		{
			if (light[i] == NULL)
			{
				lightnum = i;
				glEnable(GL_LIGHT0 + i);

				glPushMatrix();
				light[i] = new DistantLight();
				light[i]->properties(i);
				glPopMatrix();
				lightnum = 0;
				ligcolornum = 0;
				flag = true;
				break;
			}

		}
		if (flag == false){
			printf("Sorry, the system only allows 6 light sources:(\n");
		}
	}
};

class Change : public Button{
public:
	void OnMouseDown(int mousex, int mousey){

		ligcolornum = id - 10;
		GLfloat red;
		GLfloat redpos;

		GLfloat green;
		GLfloat greenpos;

		GLfloat blue;
		GLfloat bluepos;


		if (light[lightnum] != NULL)
		{
			red = (GLfloat)(light[lightnum]->light_color[id - 10]).lighting[0];
			redpos = red * 120 + 370;
			lr_pos[1] = redpos;

			green = light[lightnum]->light_color[id - 10].lighting[1];
			greenpos = green * 120 + 370;
			lg_pos[1] = greenpos;

			blue = light[lightnum]->light_color[id - 10].lighting[2];
			bluepos = blue * 120 + 370;
			lb_pos[1] = bluepos;
		}
		else
		{
			printf("Invalid operation:(\n");
		}
	}
};

class ChangeObj : public Button{
public:
	void OnMouseDown(int mousex, int mousey){

		colornum = id - 18;
		GLfloat red = Materials.material_color[colornum].materials[0];
		GLfloat redpos = red * 120 + 370;
		or_pos[1] = redpos;

		GLfloat green = Materials.material_color[colornum].materials[1];
		GLfloat greenpos = green * 120 + 370;
		og_pos[1] = greenpos;

		GLfloat blue = Materials.material_color[colornum].materials[2];
		GLfloat bluepos = blue * 120 + 370;
		ob_pos[1] = bluepos;
	}
};

class Global : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		press = true;
		if (global == 0)
		{
			global = 1;
		}

		else if (global == 1)
		{
			global = 0;
		}
	}
};

class Files1 : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		if (codenum == 1){
		
				press = true;
				ofstream SaveCode("settings(1).txt");
				SaveCode << "Lighting Properties " << endl;
				SaveCode << "Global: " << global << endl;
				for (int i = 0; i < 6; i++){
					if (light[i] != NULL)
					{
						SaveCode << endl << "light" << endl;
						SaveCode << "light: " << i << endl;
						SaveCode << "Type: " << light[i]->type() << endl;
						SaveCode << "Position: " << light[i]->position[0] << " " << light[i]->position[1] << " " << light[i]->position[2] << " " << light[i]->position[3] << endl;
						for (int l = 0; l < 3; l++){
							SaveCode << "ColorID: " << l << "  /" << light[i]->light_color[l].lighting[0] << " " << light[i]->light_color[l].lighting[1] << " " << light[i]->light_color[l].lighting[2] << endl;
						}
						SaveCode << "Direction: " << light[i]->direction[0] << " " << light[i]->direction[1] << " " << light[i]->direction[2] << " " << light[i]->direction[3] << endl;
						SaveCode << "Angle: " << light[i]->angle << endl;
						SaveCode << "Attenuation: " << light[i]->attenu << endl;
					}
				}
				SaveCode << endl << "Material Properties" << endl;
				for (int j = 0; j < 4; j++){
					//if (Materials!=NULL)
					SaveCode << "ColorID: " << j << "  /" << Materials.material_color[j].materials[0] << " " << Materials.material_color[j].materials[1] << " " << Materials.material_color[j].materials[2] << endl;
				}
				SaveCode << "Shininess: " << Materials.shininess << endl;
				SaveCode << "ObjectSize: " << Materials.scale << endl;
				SaveCode << "ObjectNo.: " << nextObject << endl;
				SaveCode.close();

				ofstream SaveFile("mySettings(1).txt");
				SaveFile << "Lighting Properties " << endl;
				SaveFile << "Global: " << global << endl;
				for (int i = 0; i < 6; i++){
					if (light[i] != NULL)
					{
						SaveFile << endl << "light" << endl;
						SaveFile << "light: " << i << endl;
						SaveFile << "Type: " << light[i]->type() << endl;
						SaveFile << "Position={ " << light[i]->position[0] << ", " << light[i]->position[1] << ", " << light[i]->position[2] << ", " << light[i]->position[3] << "};" << endl;
						for (int l = 0; l < 3; l++){
							SaveFile << "Color[" << l << "]={" << light[i]->light_color[l].lighting[0] << ", " << light[i]->light_color[l].lighting[1] << ", " << light[i]->light_color[l].lighting[2] << ", " << light[i]->light_color[l].lighting[3] << "};" << endl;
						}
						SaveFile << "Direction={ " << light[i]->direction[0] << ", " << light[i]->direction[1] << ", " << light[i]->direction[2] << ", " << light[i]->direction[3] << "};" << endl;
						SaveFile << "Angle= " << light[i]->angle << ";" << endl;
						SaveFile << "Attenuation= " << light[i]->attenu << ";" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_POSITION, Position);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_AMBIENT, Color[0]);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPECULAR, Color[1]);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_DIFFUSE, Color[2]);" << endl;
						if (SPOT == light[i]->type()){
							SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_DIRECTION, Direction);" << endl;
							SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_ANGLE, &Angle);" << endl;
							SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_ANGLE, &Attenuation);" << endl;
						}
					}
				}
				SaveFile << endl << "Material Properties" << endl;
				for (int j = 0; j < 4; j++){
					//if (Materials!=NULL)
					SaveFile << "M_Color[" << j << "]={" << Materials.material_color[j].materials[0] << ", " << Materials.material_color[j].materials[1] << ", " << Materials.material_color[j].materials[2] << ", " << Materials.material_color[j].materials[3] << "};" << endl;
				}
				SaveFile << "Shininess= " << Materials.shininess << endl;
				SaveFile << "ObjectNo.: " << nextObject << endl;
				SaveFile << "glMaterialfv(GL_FRONT, GL_AMBIENT, M_Color[0]);" << endl;
				SaveFile << "glMaterialfv(GL_FRONT, GL_SPECULAR, M_Color[1]);" << endl;
				SaveFile << "glMaterialfv(GL_FRONT, GL_DIFFUSE, M_Color[2]);" << endl;
				SaveFile << "glMaterialfv(GL_FRONT, GL_EMISSION, M_Color[3]);" << endl;
				SaveFile << "glMaterialfv(GL_FRONT, GL_SHININESS, &Shininess);" << endl;
				SaveFile.close();

			}
		
		else if (codenum == 2){
			char buffer[64];
			char subbuf[32];
			int lighttype;
			int temptemp;
			bool flag = false;

			press = true;
			ifstream in = ifstream("settings(1).txt");
			if (in){
				for (int i = 0; i < 6; i++){
					if (light[i] != NULL){
						light[i] = NULL;
						glDisable(GL_LIGHT0 + i);
						lightnum = 0;
					}
				}

				in.getline(buffer, 64);
				cout << buffer << endl;
				in.getline(buffer, 64);
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &global);


				for (int i = 0; i < 6; i++){
					in.getline(buffer, 64);// blank line
					in.getline(buffer, 64);//light or Material Properties
					cout << buffer << endl;
					cout << strcmp(buffer, "light");
					if (0 != strcmp(buffer, "light")){
						flag = true;
						break;
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &lightnum);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &lighttype);
					if (lighttype == POINT){
						light[lightnum] = new PointLight();
						/*原来可能有light[0]之类占用了这个light[lightnum], 应先释放掉再赋值，实际操作可暂时忽略。*/
					}
					else if (lighttype == SPOT){
						light[lightnum] = new SpotLight();
					}
					else if (lighttype == DISTANT){
						light[lightnum] = new DistantLight();
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f %f %f %f", subbuf, sizeof(subbuf),
						&light[lightnum]->position[0],
						&light[lightnum]->position[1],
						&light[lightnum]->position[2],
						&light[lightnum]->position[3]);
					for (int l = 0; l < 3; l++){
						in.getline(buffer, 64);
						cout << buffer << endl;
						sscanf_s(buffer, "%s %d /%f %f %f", subbuf, sizeof(subbuf),
							&temptemp,
							&light[lightnum]->light_color[l].lighting[0],
							&light[lightnum]->light_color[l].lighting[1],
							&light[lightnum]->light_color[l].lighting[2]);
						cout << lightnum << endl;
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f %f %f %f", subbuf, sizeof(subbuf),
						&light[lightnum]->direction[0],
						&light[lightnum]->direction[1],
						&light[lightnum]->direction[2],
						&light[lightnum]->direction[3]);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &light[lightnum]->angle);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &light[lightnum]->attenu);

					glEnable(GL_LIGHT0 + lightnum);
				}
				lightnum = 0;
				if (flag == false){
					in.getline(buffer, 64);//
					cout << buffer << endl;
				}

				for (int j = 0; j < 4; j++){
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d /%f %f %f", subbuf, sizeof(subbuf),
						&temptemp,
						&Materials.material_color[j].materials[0],
						&Materials.material_color[j].materials[1],
						&Materials.material_color[j].materials[2]);
				}
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &Materials.shininess);
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &Materials.scale);
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &nextObject);

			}
		}
	}
};

class Files2 : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		if (codenum == 1)
		{
			press = true;
			ofstream SaveCode("settings(2).txt");
			SaveCode << "Lighting Properties " << endl;
			SaveCode << "Global: " << global << endl;
			for (int i = 0; i < 6; i++)
			{
				if (light[i] != NULL)
				{
					SaveCode << endl << "light" << endl;
					SaveCode << "light: " << i << endl;
					SaveCode << "Type: " << light[i]->type() << endl;
					SaveCode << "Position: " << light[i]->position[0] << " " << light[i]->position[1] << " " << light[i]->position[2] << " " << light[i]->position[3] << endl;
					for (int l = 0; l < 3; l++)
					{
						SaveCode << "ColorID: " << l << "  /" << light[i]->light_color[l].lighting[0] << " " << light[i]->light_color[l].lighting[1] << " " << light[i]->light_color[l].lighting[2] << endl;
					}
					SaveCode << "Direction: " << light[i]->direction[0] << " " << light[i]->direction[1] << " " << light[i]->direction[2] << " " << light[i]->direction[3] << endl;
					SaveCode << "Angle: " << light[i]->angle << endl;
					SaveCode << "Attenuation: " << light[i]->attenu << endl;
				}
			}
			SaveCode << endl << "Material Properties" << endl;
			for (int j = 0; j < 4; j++)
			{
				//if (Materials!=NULL)
				SaveCode << "ColorID: " << j << "  /" << Materials.material_color[j].materials[0] << " " << Materials.material_color[j].materials[1] << " " << Materials.material_color[j].materials[2] << endl;
			}
			SaveCode << "Shininess: " << Materials.shininess << endl;
			SaveCode << "ObjectSize: " << Materials.scale << endl;
			SaveCode << "ObjectNo.: " << nextObject << endl;
			SaveCode.close();

			ofstream SaveFile("mySettings(2).txt");
			SaveFile << "Lighting Properties " << endl;
			SaveFile << "Global: " << global << endl;
			for (int i = 0; i < 6; i++)
			{
				if (light[i] != NULL)
				{
					SaveFile << endl << "light" << endl;
					SaveFile << "light: " << i << endl;
					SaveFile << "Type: " << light[i]->type() << endl;
					SaveFile << "Position={ " << light[i]->position[0] << ", " << light[i]->position[1] << ", " << light[i]->position[2] << ", " << light[i]->position[3] << "};" << endl;
					for (int l = 0; l < 3; l++)
					{
						SaveFile << "Color[" << l << "]={" << light[i]->light_color[l].lighting[0] << ", " << light[i]->light_color[l].lighting[1] << ", " << light[i]->light_color[l].lighting[2] << ", " << light[i]->light_color[l].lighting[3] << "};" << endl;
					}
					SaveFile << "Direction={ " << light[i]->direction[0] << ", " << light[i]->direction[1] << ", " << light[i]->direction[2] << ", " << light[i]->direction[3] << "};" << endl;
					SaveFile << "Angle= " << light[i]->angle << ";" << endl;
					SaveFile << "Attenuation= " << light[i]->attenu << ";" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_POSITION, Position);" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_AMBIENT, Color[0]);" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPECULAR, Color[1]);" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_DIFFUSE, Color[2]);" << endl;
					if (SPOT == light[i]->type()){
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_DIRECTION, Direction);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_ANGLE, &Angle);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_ANGLE, &Attenuation);" << endl;
					}
				}
			}
			SaveFile << endl << "Material Properties" << endl;
			for (int j = 0; j < 4; j++)
			{
				//if (Materials!=NULL)
				SaveFile << "M_Color[" << j << "]={" << Materials.material_color[j].materials[0] << ", " << Materials.material_color[j].materials[1] << ", " << Materials.material_color[j].materials[2] << ", " << Materials.material_color[j].materials[3] << "};" << endl;
			}
			SaveFile << "Shininess= " << Materials.shininess << endl;
			SaveFile << "ObjectNo.: " << nextObject << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_AMBIENT, M_Color[0]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_SPECULAR, M_Color[1]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_DIFFUSE, M_Color[2]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_EMISSION, M_Color[3]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_SHININESS, &Shininess);" << endl;
			SaveFile.close();
		}
		else if (codenum == 2){
			char buffer[64];
			char subbuf[32];
			int lighttype;
			int temptemp;
			bool flag = false;


			press = true;
			ifstream in = ifstream("settings(2).txt");
			if (in){
				for (int i = 0; i < 6; i++){
					if (light[i] != NULL){
						light[i] = NULL;
						glDisable(GL_LIGHT0 + i);
						lightnum = 0;
					}
				}

				in.getline(buffer, 64);
				cout << buffer << endl;
				in.getline(buffer, 64);
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &global);


				for (int i = 0; i < 6; i++){
					in.getline(buffer, 64);// blank line
					in.getline(buffer, 64);//light or Material Properties
					cout << buffer << endl;
					cout << strcmp(buffer, "light");
					if (0 != strcmp(buffer, "light")){
						flag = true;
						break;
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &lightnum);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &lighttype);
					if (lighttype == POINT){
						light[lightnum] = new PointLight();
						/*原来可能有light[0]之类占用了这个light[lightnum], 应先释放掉再赋值，实际操作可暂时忽略。*/
					}
					else if (lighttype == SPOT){
						light[lightnum] = new SpotLight();
					}
					else if (lighttype == DISTANT){
						light[lightnum] = new DistantLight();
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f %f %f %f", subbuf, sizeof(subbuf),
						&light[lightnum]->position[0],
						&light[lightnum]->position[1],
						&light[lightnum]->position[2],
						&light[lightnum]->position[3]);
					for (int l = 0; l < 3; l++){
						in.getline(buffer, 64);
						cout << buffer << endl;
						sscanf_s(buffer, "%s %d /%f %f %f", subbuf, sizeof(subbuf),
							&temptemp,
							&light[lightnum]->light_color[l].lighting[0],
							&light[lightnum]->light_color[l].lighting[1],
							&light[lightnum]->light_color[l].lighting[2]);
						cout << lightnum << endl;
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f %f %f %f", subbuf, sizeof(subbuf),
						&light[lightnum]->direction[0],
						&light[lightnum]->direction[1],
						&light[lightnum]->direction[2],
						&light[lightnum]->direction[3]);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &light[lightnum]->angle);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &light[lightnum]->attenu);

					glEnable(GL_LIGHT0 + lightnum);
				}
				lightnum = 0;
				if (flag == false){
					in.getline(buffer, 64);//
					cout << buffer << endl;
				}

				for (int j = 0; j < 4; j++){
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d /%f %f %f", subbuf, sizeof(subbuf),
						&temptemp,
						&Materials.material_color[j].materials[0],
						&Materials.material_color[j].materials[1],
						&Materials.material_color[j].materials[2]);
				}
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &Materials.shininess);
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &Materials.scale);
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &nextObject);
			}
		}
	}
};

class Files3 : public Button{
public:
	void OnMouseDown(int mousex, int mousey)
	{
		if (codenum == 1)
		{
			press = true;
			ofstream SaveCode("settings(3).txt");
			SaveCode << "Lighting Properties " << endl;
			SaveCode << "Global: " << global << endl;
			for (int i = 0; i < 6; i++)
			{
				if (light[i] != NULL)
				{
					SaveCode << endl << "light" << endl;
					SaveCode << "light: " << i << endl;
					SaveCode << "Type: " << light[i]->type() << endl;
					SaveCode << "Position: " << light[i]->position[0] << " " << light[i]->position[1] << " " << light[i]->position[2] << " " << light[i]->position[3] << endl;
					for (int l = 0; l < 3; l++)
					{
						SaveCode << "ColorID: " << l << "  /" << light[i]->light_color[l].lighting[0] << " " << light[i]->light_color[l].lighting[1] << " " << light[i]->light_color[l].lighting[2] << endl;
					}
					SaveCode << "Direction: " << light[i]->direction[0] << " " << light[i]->direction[1] << " " << light[i]->direction[2] << " " << light[i]->direction[3] << endl;
					SaveCode << "Angle: " << light[i]->angle << endl;
					SaveCode << "Attenuation: " << light[i]->attenu << endl;
				}
			}
			SaveCode << endl << "Material Properties" << endl;
			for (int j = 0; j < 4; j++)
			{
				//if (Materials!=NULL)
				SaveCode << "ColorID: " << j << "  /" << Materials.material_color[j].materials[0] << " " << Materials.material_color[j].materials[1] << " " << Materials.material_color[j].materials[2] << endl;
			}
			SaveCode << "Shininess: " << Materials.shininess << endl;
			SaveCode << "ObjectSize: " << Materials.scale << endl;
			SaveCode << "ObjectNo.: " << nextObject << endl;
			SaveCode.close();

			ofstream SaveFile("mySettings(3).txt");
			SaveFile << "Lighting Properties " << endl;
			SaveFile << "Global: " << global << endl;
			for (int i = 0; i < 6; i++)
			{
				if (light[i] != NULL)
				{
					SaveFile << endl << "light" << endl;
					SaveFile << "light: " << i << endl;
					SaveFile << "Type: " << light[i]->type() << endl;
					SaveFile << "Position={ " << light[i]->position[0] << ", " << light[i]->position[1] << ", " << light[i]->position[2] << ", " << light[i]->position[3] << "};" << endl;
					for (int l = 0; l < 3; l++)
					{
						SaveFile << "Color[" << l << "]={" << light[i]->light_color[l].lighting[0] << ", " << light[i]->light_color[l].lighting[1] << ", " << light[i]->light_color[l].lighting[2] << ", " << light[i]->light_color[l].lighting[3] << "};" << endl;
					}
					SaveFile << "Direction={ " << light[i]->direction[0] << ", " << light[i]->direction[1] << ", " << light[i]->direction[2] << ", " << light[i]->direction[3] << "};" << endl;
					SaveFile << "Angle= " << light[i]->angle << ";" << endl;
					SaveFile << "Attenuation= " << light[i]->attenu << ";" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_POSITION, Position);" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_AMBIENT, Color[0]);" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPECULAR, Color[1]);" << endl;
					SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_DIFFUSE, Color[2]);" << endl;
					if (SPOT == light[i]->type())
					{
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_DIRECTION, Direction);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_ANGLE, &Angle);" << endl;
						SaveFile << "glLightfv(GL_LIGHT" << i << ", " << "GL_SPOT_ANGLE, &Attenuation);" << endl;
					}
				}
			}
			SaveFile << endl << "Material Properties" << endl;
			for (int j = 0; j < 4; j++)
			{
				//if (Materials!=NULL)
				SaveFile << "M_Color[" << j << "]={" << Materials.material_color[j].materials[0] << ", " << Materials.material_color[j].materials[1] << ", " << Materials.material_color[j].materials[2] << ", " << Materials.material_color[j].materials[3] << "};" << endl;
			}
			SaveFile << "Shininess= " << Materials.shininess << endl;
			SaveFile << "ObjectNo.: " << nextObject << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_AMBIENT, M_Color[0]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_SPECULAR, M_Color[1]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_DIFFUSE, M_Color[2]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_EMISSION, M_Color[3]);" << endl;
			SaveFile << "glMaterialfv(GL_FRONT, GL_SHININESS, &Shininess);" << endl;
			SaveFile.close();
		}


		else if (codenum == 2){
			char buffer[64];
			char subbuf[32];
			int lighttype;
			int temptemp;
			bool flag = false;

			press = true;
			ifstream in = ifstream("settings(3).txt");
			if (in){
				for (int i = 0; i < 6; i++){
					if (light[i] != NULL){
						light[i] = NULL;
						glDisable(GL_LIGHT0 + i);
						lightnum = 0;
					}
				}

				in.getline(buffer, 64);
				cout << buffer << endl;
				in.getline(buffer, 64);
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &global);


				for (int i = 0; i < 6; i++)
				{
					in.getline(buffer, 64);// blank line
					in.getline(buffer, 64);//light or Material Properties
					cout << buffer << endl;
					cout << strcmp(buffer, "light");
					if (0 != strcmp(buffer, "light"))
					{
						flag = true;
						break;
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &lightnum);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &lighttype);
					if (lighttype == POINT){
						light[lightnum] = new PointLight();
						/*原来可能有light[0]之类占用了这个light[lightnum], 应先释放掉再赋值，实际操作可暂时忽略。*/
					}
					else if (lighttype == SPOT)
					{
						light[lightnum] = new SpotLight();
					}
					else if (lighttype == DISTANT)
					{
						light[lightnum] = new DistantLight();
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f %f %f %f", subbuf, sizeof(subbuf),
						&light[lightnum]->position[0],
						&light[lightnum]->position[1],
						&light[lightnum]->position[2],
						&light[lightnum]->position[3]);
					for (int l = 0; l < 3; l++)
					{
						in.getline(buffer, 64);
						cout << buffer << endl;
						sscanf_s(buffer, "%s %d /%f %f %f", subbuf, sizeof(subbuf),
							&temptemp,
							&light[lightnum]->light_color[l].lighting[0],
							&light[lightnum]->light_color[l].lighting[1],
							&light[lightnum]->light_color[l].lighting[2]);
						cout << lightnum << endl;
					}
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f %f %f %f", subbuf, sizeof(subbuf),
						&light[lightnum]->direction[0],
						&light[lightnum]->direction[1],
						&light[lightnum]->direction[2],
						&light[lightnum]->direction[3]);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &light[lightnum]->angle);
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &light[lightnum]->attenu);

					glEnable(GL_LIGHT0 + lightnum);
				}
				lightnum = 0;
				if (flag == false)
				{
					in.getline(buffer, 64);//
					cout << buffer << endl;
				}

				for (int j = 0; j < 4; j++)
				{
					in.getline(buffer, 64);
					cout << buffer << endl;
					sscanf_s(buffer, "%s %d /%f %f %f", subbuf, sizeof(subbuf),
						&temptemp,
						&Materials.material_color[j].materials[0],
						&Materials.material_color[j].materials[1],
						&Materials.material_color[j].materials[2]);
				}
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &Materials.shininess);
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %f", subbuf, sizeof(subbuf), &Materials.scale);
				in.getline(buffer, 64);
				cout << buffer << endl;
				sscanf_s(buffer, "%s %d", subbuf, sizeof(subbuf), &nextObject);
			}
		}
	}	
};

class Question : public Button{

};

CreatePoint pBtnPoint;
CreateSpot pBtnSpot;
CreateDistant pBtnDistant;
RadioButton pBtnAmbL;
RadioButton pBtnSpeL;
RadioButton pBtnDifL;
Global pBtnGlobal;
CodeRadio pBtnSave;
CodeRadio pBtnLoad;
Next pBtnNext;
Previous pBtnPrevious;

MaterialRadio pBtnAmbO;
MaterialRadio pBtnSpeO;
MaterialRadio pBtnDifO;
MaterialRadio pBtnEmiO;

Animation pBtnAnimation;

ObjectRadio pBtnRotate;
ObjectRadio pBtnTranslate;

Files1 pBtnFile1;
Files2 pBtnFile2;
Files3 pBtnFile3;

Question pBtnHint;

Button *pBtn[] = { &pBtnPoint, &pBtnSpot, &pBtnDistant,
&pBtnAmbL, &pBtnSpeL, &pBtnDifL,
&pBtnGlobal, &pBtnSave, &pBtnLoad,
&pBtnNext, &pBtnPrevious,
&pBtnAmbO, &pBtnSpeO, &pBtnDifO, &pBtnEmiO,
&pBtnAnimation,&pBtnRotate,&pBtnTranslate,&pBtnOxa,&pBtnOya,&pBtnOza,&pBtnFile1,&pBtnFile2,&pBtnFile3,&pBtnHint
};

class Slider : public Button {
public:
	Slider(){};
};

Slider pSldAttenu;
Slider pSldAngle;
Slider pSldLx;
Slider pSldLy;
Slider pSldLz;
Slider pSldLr;
Slider pSldOr;
Slider pSldLg;
Slider pSldOg;
Slider pSldOb;
Slider pSldLb;
Slider pSldShin;
Slider pSldScale;

void DNA(){
	int i;
	glTranslatef(-7, 0, 0);
	for (i = 0; i <= 24; i++){
		glPushMatrix();
		glTranslatef(0.6*i, 0, 0);
		glRotatef(15 * i, 1, 0, 0);
		glScalef(0.25, 0.25, 3);
		glutSolidCube(1);
		glPopMatrix();
	}
	for (i = 0; i <= 24; i++){
		float theta = 15 * i;
		glPushMatrix();
		glRotatef(theta, 1, 0, 0);
		glTranslatef(0.6*i, 0, 1.5);
		glutSolidSphere(0.4, 30, 30);
		glPopMatrix();
	}

	for (i = 0; i <= 24; i++){
		float theta = 15 * i;
		glPushMatrix();
		glRotatef(theta, 1, 0, 0);
		glTranslatef(0.6*i, 0, -1.5);
		glutSolidSphere(0.4, 30, 30);
		glPopMatrix();
	}
}

void stick(int theTA){
	glTranslatef(0, 0, 1.5);
	glRotatef(theTA, 1, 0, 0);
	glScalef(0.7, 3.5, 0.2);
	glutSolidCube(1);
}

void stickII(int theTA, int max){
	for (int i = 0; i < max; i++){
		glPushMatrix();
		glRotatef(360 / max * i, 0, 1, 0);
		glTranslatef(0, 0, 1.5);
		glRotatef(theTA, 1, 0, 0);
		glScalef(0.7, 3.5, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}
}

void stickIII(int theTA, int max){
	for (int i = 0; i < max; i++){
		glPushMatrix();
		glRotatef(360 / max * i, 0, 1, 0);
		glTranslatef(0, 0, 15);
		//glRotatef(theTA, 0, 0, 1);
		glutSolidSphere(2, 40, 40);
		glScalef(1.5, 30, 1.5);
		glutSolidCube(1);
		
		glPopMatrix();
	}
}

void wing(int theTA){
	glPushMatrix();
	glutSolidSphere(0.5, 25, 25);
	glRotatef(theta[HELI], 0, 1, 0);
	stickII(theTA, 6);
	glPopMatrix();
}

void mainBody(){
	glPushMatrix();
	glScalef(2, 1.8, 2.2);
	glutSolidIcosahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 1);
	gluCylinder(obj, 0.6, 0.3, 5, 500, 500);
	glTranslatef(0, 0, 5);
	glutSolidSphere(0.3, 10, 10);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.3, 1.5, 10, 10);
	glPopMatrix();
}

void underCarriage(){
	int theTA = 0;
	for (int i = 0; i < 11; i++){
		glPushMatrix();
		glRotatef(18 * i, 0, 1, 0);
		glScalef(0.8, 0.3, 0.8);
		stick(theTA);
		glPopMatrix();
	}
}

void helicopter(){
	glPushMatrix();
	int theTA = 80;
	mainBody();
	glTranslatef(0, 2, 0);
	wing(theTA);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.1, 1.4, 6);
	glRotatef(90, 0, 0, 1);
	glScalef(0.25, 0.25, 0.25);
	theTA = 75;
	wing(theTA);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 1.4, 6);
	glRotatef(90, 0, 0, 1);
	glRotatef(30, 0, 1, 0);
	glScalef(0.25, 0.25, 0.25);
	theTA = 105;
	wing(theTA);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.9, 0.9, 0.9);
	underCarriage();
	glPopMatrix();
}

void highTower(){
	glPushMatrix();
	int theTA = 0;
	for (int i = 0; i < 18; i++){
		glPushMatrix();
		glTranslatef(0, -1.5, 0);
		glRotatef(20 * i, 0, 1, 0);
		glScalef(0.2, 1.0, 0.2);
		stick(theTA);
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCone(0.4, 0.6, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -0.8);
	gluCylinder(obj, 0.4, 0.4, 0.8, 140, 140);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.8, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.5, 1.5, 10, 10);
	glPopMatrix();
}

void shortTower(){
	glPushMatrix();
	int theTA = 0;
	for (int i = 0; i < 12; i++){
		glPushMatrix();
		glTranslatef(0, -0.8, 0);
		glRotatef(30 * i, 0, 1, 0);
		glScalef(0.2, 0.5, 0.2);
		stick(theTA);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.4, 0.8, 10, 10);
	glPopMatrix();
}

void aWall(){
	glPushMatrix();
	glScalef(0.7, 2, 3);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0, 0, -1.4);
	for (int a = 0; a <= 7; a++){
		glPushMatrix();
		glTranslatef(0.3, 1.1, 0.4*a);
		glScalef(0.15, 0.2, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}

	glTranslatef(-0.6, 0, 0);
	for (int a = 0; a <= 7; a++){
		glPushMatrix();
		glTranslatef(0.3, 1.1, 0.4*a);
		glScalef(0.15, 0.2, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}
}

void castle(){
	glPushMatrix();
	glTranslatef(-2, 0, 2);
	highTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 0, -2);
	highTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 0, 2);
	highTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, 0, -2);
	highTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -2, 0);
	glScalef(0.8, 1.2, 1.2);
	aWall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -2, 0);
	glScalef(0.8, 1.2, 1.2);
	aWall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2, -2);
	glRotatef(90, 0, 1, 0);
	glScalef(0.8, 1.2, 1.2);
	aWall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2, 2);
	glRotatef(90, 0, 1, 0);
	glScalef(0.8, 1.2, 1.2);
	aWall();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1.76, 0);
	glScalef(0.8, 1.2, 0.8);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.4, 0);
	highTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 0, 0.8);
	shortTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8, 0, 0.8);
	shortTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, 0, -0.8);
	shortTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8, 0, -0.8);
	shortTower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -3, 0);
	glScalef(4, 0.5, 4);
	glutSolidCube(1);
	glPopMatrix();
}

void goatLowerLegs(){
	glPushMatrix();
	glScaled(0.3, 0.8, 0.3);
	glutSolidCube(1);
	glTranslatef(-0.3, 0.5, 0);
	glScalef(6, 1.5, 5);
	glutSolidSphere(0.2, 10, 10);
	glPopMatrix();
}

void goatBody(){
	glPushMatrix();
	glTranslated(-1, 2.2, 0);
	glutSolidSphere(0.85, 25, 25);
	glPopMatrix();
	glPushMatrix();
	glScaled(1, 0.8, 0.8);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, 1.25, 0);
	glScaled(0.7, 1.5, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, 2.7, -0.7);
	glRotated(45, 0, 0, 1);
	glScaled(0.6, 0.6, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, 2.7, 0.7);
	glRotated(45, 0, 0, 1);
	glScaled(0.6, 0.6, 0.3);
	glutSolidCube(1);
	glPopMatrix();
}
void goat(){
	glPushMatrix();
	goatBody();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, -0.7, -0.4);
	glRotatef(90, 1, 0, 0);
	gluCylinder(obj, 0.25, 0.26, 1, 100, 100);
	glTranslatef(0, 0, 1.4);
	glRotatef(90, 1, 0, 0);
	goatLowerLegs();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, -0.7, 0.4);
	glRotatef(90, 1, 0, 0);
	gluCylinder(obj, 0.25, 0.26, 1, 100, 100);
	glTranslatef(0, 0, 1.4);
	glRotatef(90, 1, 0, 0);
	goatLowerLegs();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1, -0.7, 0.4);
	glRotatef(90, 1, 0, 0);
	gluCylinder(obj, 0.25, 0.26, 1, 100, 100);
	glTranslatef(0, 0, 1.4);
	glRotatef(90, 1, 0, 0);
	goatLowerLegs();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1, -0.7, -0.4);
	glRotatef(90, 1, 0, 0);
	gluCylinder(obj, 0.25, 0.26, 1, 100, 100);
	glTranslatef(0, 0, 1.4);
	glRotatef(90, 1, 0, 0);
	goatLowerLegs();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.6, 0.7, 0);
	glutSolidSphere(0.25, 20, 20);
	glPopMatrix();
}

void aCube(){
	glPushMatrix();
	glScalef(30, 1.5, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5,7.5,0);
	glRotatef(-45,0,0,1);
	glScalef(20, 1.5, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5, -7.5, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(20, 1.5, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -7.5, -7.5);
	glRotatef(45, 1, 0, 0);
	glScalef(1.5, 1.5, 20);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 7.5, 7.5);
	glRotatef(45, 1, 0, 0);
	glScalef(1.5, 1.5, 20);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 30, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 30);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 15);
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 15, 0);
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -15, 0);
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -15);
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, 0);
	glutSolidSphere(2.6, 50, 50);
	glPopMatrix();
}

void wheel(){
	glPushMatrix();
	glTranslatef(0,15,0);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(3, 15, 70, 70);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -15, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(3, 15, 70, 70);
	glPopMatrix();

	glPushMatrix();
	stickIII(15, 18);
	glPopMatrix();
}

void arrow(){
	glPushMatrix();
	glTranslatef(10, 0, 0);//arrow
	glScalef(30, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, 2, 0);//arrow
	glRotatef(30, 0, 0, 1);
	glScalef(6, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, -2, 0);//arrow
	glRotatef(-30, 0, 0, 1);
	glScalef(6, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
}

void arrow2(){
	glPushMatrix();
	glTranslatef(3, 0, 0);//arrow
	glScalef(10, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, 2, 0);//arrow
	glRotatef(30, 0, 0, 1);
	glScalef(6, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, -2, 0);//arrow
	glRotatef(-30, 0, 0, 1);
	glScalef(6, 1, 0);
	glutSolidCube(1);
	glPopMatrix();
}

void point(){
	glPushMatrix();
	glutSolidSphere(4,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, 0, 0);
	glScalef(0.6, 1, 1);
	arrow();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, 0, 0);
	glRotatef(180,0,0,1);
	glScalef(0.6, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(-90, 0, 0, 1);
	glScalef(0.5, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -10, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.5, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 10, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(0.55, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, -10, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.55, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, -10, 0);
	glRotatef(135, 0, 0, 1);
	glScalef(0.55, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 10, 0);
	glRotatef(-135, 0, 0, 1);
	glScalef(0.55, 1, 1);
	arrow();
	glPopMatrix();
}

void spot(){
	glPushMatrix();
	glutSolidSphere(5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-10,0);
	glRotatef(-75,0,0,1);
	glScalef(15, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 0, 0);
	glRotatef(-15, 0, 0, 1);
	glScalef(35, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -15, 0);
	glRotatef(135, 0, 0, 1);
	glScalef(0.9, 1, 1);
	arrow();
	glPopMatrix();
}

void distant(){
	glPushMatrix();
	glScalef(45, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 4, 0);
	glRotatef(70, 0, 0, 1);
	glScalef(0.7, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 4, 0);
	glRotatef(70, 0, 0, 1);
	glScalef(0.7, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 4, 0);
	glRotatef(70, 0, 0, 1);
	glScalef(0.7, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 4, 0);
	glRotatef(70, 0, 0, 1);
	glScalef(0.7, 1, 1);
	arrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, 4, 0);
	glRotatef(70, 0, 0, 1);
	glScalef(0.7, 1, 1);
	arrow();
	glPopMatrix();
}

void globalLight(){
	glPushMatrix();
	glTranslatef(16, 0, 0);
	glScalef(1, 1, 1);
	arrow2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-16, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(1, 1, 1);
	arrow2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -8, 0);
	glRotatef(-90, 0, 0, 1);
	glScalef(0.6, 1, 1);
	arrow2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 8, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.6, 1, 1);
	arrow2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, -9, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(0.9, 1, 1);
	arrow2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, 9, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.9, 1, 1);
	arrow2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13, 9, 0);
	glRotatef(135, 0, 0, 1);
	glScalef(0.9, 1, 1);
	arrow2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13, -9, 0);
	glRotatef(-135, 0, 0, 1);
	glScalef(0.9, 1, 1);
	arrow2();
	glPopMatrix();
}

void arrow3(){
	glPushMatrix();
	glTranslatef(-3, 4, 0);//arrow
	glRotatef(35, 0, 0, 1);
	glScalef(15, 2, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3, -4, 0);//arrow
	glRotatef(-35, 0, 0, 1);
	glScalef(15, 2, 0);
	glutSolidCube(1);
	glPopMatrix();
}