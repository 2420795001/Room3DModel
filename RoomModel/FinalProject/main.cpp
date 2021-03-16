#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <bits/stdc++.h>

#define ID_TIMER    1                        // �Զ���תʱ��
#define PI 3.14159
#define BMP_Header_Length 54  //ͼ���������ڴ���е�ƫ����

GLuint texFloor;
GLuint texShip;
GLuint texSea;
GLuint texCarpet;
GLuint texDoor;
GLuint texSky;
GLfloat ylookAt = 2;
GLfloat zlookAt = 5.0;
GLfloat xlookAt = 0.0;

GLuint control = 0;
GLuint projector = 0;

GLfloat rotStep = 30.0f;
GLfloat paceStep = 30.0f;
GLfloat moveStep = 0.05f;
GLfloat backRot = 0.0f;
GLfloat lookStep = 0.1f;
GLboolean flag = false;
GLboolean flag2 = false;                     //���ƺ���
GLboolean flag3 = false;                     //����ǰ��
GLboolean flag4 = false;


GLfloat xRot;                           // ������X�������ת���ٶȶ���
GLfloat yRot;                           // ������Y�������ת���ٶȶ���
GLfloat zRot;                           // ������Z�������ת���ٶȶ���

GLfloat armL;
GLfloat armR;

GLfloat legL = 15.0f;
GLfloat legR = -15.0f;

const int n = 10000;
GLfloat R1 = 0;
GLfloat R2 = 0;

GLfloat xPosition;                           // X�����λ�ö���
GLfloat yPosition;                           // Y�����λ�ö���
GLfloat zPosition;                           // Z�����λ�ö���

GLfloat xPosition_person;
GLfloat yPosition_person;
GLfloat zPosition_person;

GLfloat color[4]={0.0f, 0.0f, 0.0f, 1.0f};

GLboolean keys[256];                                         // ���ڼ������̵�����
static GLboolean mouseFlag = FALSE;

GLuint load_texture(const char* file_name);
int power_of_two(int n);
void SetupRC();
GLvoid Init();
GLvoid ChangeSize(GLsizei, GLsizei);
GLvoid Draw3D1();
GLvoid Draw3D2();
GLvoid Draw3D3();
GLvoid Draw3D();
GLuint KeyPress();
GLuint MainWndMenu();
GLvoid CALLBACK timerProc(HWND,UINT,UINT,DWORD);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        // ������̺�������
int commandBtns(HWND);


HINSTANCE hInstance;                                         // ϵͳʵ�����
HWND      hWndMain;                                          // ��������
HMENU     hPopup;
HWND      hWnd;                                              // ��������������
HDC       hDC;                                               // �豸�������������
PIXELFORMATDESCRIPTOR pfd;                                   // ���ظ�ʽ�ṹ��������
HGLRC     hGLRC;                                             // OpenGL��Ⱦ�������������

HMENU hMenuMain;                                             // ������˵����
HMENU hMenuWindow;
#define WINDOW_MENU_POS    1000
#define IDM_CTRL           2001
#define IDM_AUTO           2002
#define IDM_STOP           2003
#define IDM_BLACK          2004
#define IDM_GRAY           2005
#define IDM_SKYBLUE        2006
#define IDM_WHITE          2007

HWND    hLabel;
HWND    hCmdBtns;

#define IDC_FRAME          10000                // ��ܿؼ�Ψһ��ʶ
#define IDC_RotateX1       10001                // ��ť�ؼ�Ψһ��ʶ
#define IDC_RotateX2       10002                // ��ť�ؼ�Ψһ��ʶ
#define IDC_RotateY1       10003                // ��ť�ؼ�Ψһ��ʶ
#define IDC_RotateY2       10004                // ��ť�ؼ�Ψһ��ʶ
#define IDC_RotateZ1       10005                // ��ť�ؼ�Ψһ��ʶ
#define IDC_RotateZ2       10006                // ��ť�ؼ�Ψһ��ʶ

#define IDC_TranslateX1    10011                // ��ť�ؼ�Ψһ��ʶ
#define IDC_TranslateX2    10012                // ��ť�ؼ�Ψһ��ʶ
#define IDC_TranslateY1    10013                // ��ť�ؼ�Ψһ��ʶ
#define IDC_TranslateY2    10014                // ��ť�ؼ�Ψһ��ʶ
#define IDC_TranslateZ1    10015                // ��ť�ؼ�Ψһ��ʶ
#define IDC_TranslateZ2    10016                // ��ť�ؼ�Ψһ��ʶ
#define IDC_Room1          10017                // ��ť�ؼ�Ψһ��ʶ
#define IDC_Room2          10018                // ��ť�ؼ�Ψһ��ʶ
#define IDC_ON             10019                // ��ť�ؼ�Ψһ��ʶ
#define IDC_OFF            10020                // ��ť�ؼ�Ψһ��ʶ

//********************************************************************
//*  ��OpenGL�¼�����                                              *
//********************************************************************
//
GLuint Open(HWND phWnd)
{
  hWnd = phWnd;

  hDC = GetDC(hWnd);

  pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);                          // ��ʽ�������Ĵ�С
  pfd.nVersion        = 1;                       // �汾��
  pfd.dwFlags         = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER; // ֧�ִ���˫����OPENGL
  pfd.dwLayerMask     = PFD_MAIN_PLANE;          //
  pfd.iPixelType      = PFD_TYPE_RGBA;           // RGBA��ʽ
  pfd.cColorBits      = 24;                      // ɫ�����
  pfd.cRedBits        = 0;                       // ���Ե�ɫ��λ
  pfd.cRedShift       = 0;                       // ���Ե�ɫ��λ
  pfd.cGreenBits      = 0;                       // ���Ե�ɫ��λ
  pfd.cGreenShift     = 0;                       // ���Ե�ɫ��λ
  pfd.cBlueBits       = 0;                       // ���Ե�ɫ��λ
  pfd.cBlueShift      = 0;                       // ���Ե�ɫ��λ
  pfd.cAlphaBits      = 0;                       // ��Alpha����
  pfd.cAlphaShift     = 0;                       // ����Shift Bit
  pfd.cAccumBits      = 0;                       // �޾ۼ�����
  pfd.cAccumRedBits   = 0;                       // ���Ծۼ�λ
  pfd.cAccumGreenBits = 0;                       // ���Ծۼ�λ
  pfd.cAccumBlueBits  = 0;                       // ���Ծۼ�λ
  pfd.cAccumAlphaBits = 0;                       // ���Ծۼ�λ
  pfd.cDepthBits      = 24;                      // 24λ Z-���� (��Ȼ���)
  pfd.cStencilBits    = 0;                       // ��ģ�建��
  pfd.cAuxBuffers     = 0;                       // �޸�������
  pfd.iLayerType      = 0;                       // ����ͼ��
  pfd.bReserved       = 0;                       // ����
  pfd.iLayerType      = 0;                       // ���Բ�����
  pfd.dwVisibleMask   = 0;                       // ���Բ�����
  pfd.dwDamageMask    = 0;                       // ���Բ�����

  int pixelformat = ChoosePixelFormat(hDC, &pfd);

  SetPixelFormat(hDC, pixelformat, &pfd);

  hGLRC = wglCreateContext(hDC);

  wglMakeCurrent(hDC,hGLRC);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);          // ��ʼ������Ϊ��ɫ

  return 0;
} // ��OpenGL�¼�����

/********************************************************************/
/*  ��������ע�ắ������                                            */
/********************************************************************/
//
GLuint MainWndCls()
{
  //��������ע�ắ������
  WNDCLASSEX wcex;
  wcex.cbSize        = sizeof(WNDCLASSEX);
  wcex.style         = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
  wcex.lpfnWndProc   = (WNDPROC)WndProc;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hInstance     = hInstance;
  wcex.hIcon         = LoadIcon(hInstance,(LPCTSTR)IDI_APPLICATION);
  wcex.hCursor       = LoadCursor(NULL,IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wcex.lpszMenuName  = NULL;
  wcex.lpszClassName = TEXT("WndCls");
  wcex.hIconSm       = LoadIcon(NULL,(LPCTSTR)IDI_APPLICATION);

  if(!RegisterClassEx(&wcex)) return 1;
  return 0;
} // ��������ע�ắ��

/********************************************************************/
/*  ���������庯������                                              */
/********************************************************************/
//
GLuint MainWndCreate()
{
  //����������
  hWndMain = CreateWindowEx(WS_EX_CLIENTEDGE,
                        TEXT("WndCls"),
                        TEXT("OpenGL-Windows GUI!"),
                        WS_OVERLAPPED   |   WS_SYSMENU   |WS_MINIMIZEBOX|WS_CLIPCHILDREN,
                        100, 100, 1400, 600,
                        NULL,
                        hMenuMain,
                        hInstance,
                        NULL);

  if(!hWndMain) return 1;

  ShowWindow(hWndMain,SW_SHOWNORMAL);
  UpdateWindow(hWndMain);

  Init();

  return 0;
} // ���������庯��

//********************************************************************
//*  ��������̺�������                                          *
//********************************************************************
//
LRESULT CALLBACK WndProc(HWND   hWnd,
                         UINT   message,
                         WPARAM wParam,
                         LPARAM lParam)
{
  POINT pt;
  POINT ptCurr;
  PAINTSTRUCT ps;
  switch (message)
  {
    case WM_CREATE:                                  // ���崴��ѶϢ
      commandBtns(hWnd);
      Open(hWnd);
      break;

    case WM_PAINT:                                   // ���»���ѶϢ
      BeginPaint(hWnd,&ps);
      SetCursor (LoadCursor (NULL, IDC_HAND));

      Draw3D();
      if(!flag){
        flag = true;
        SendMessage(hWnd, WM_PAINT, 0, 0L);
      }

      EndPaint(hWnd,&ps);
      break;

    case WM_SIZE:                                    // �ı䴰���СѶϢ
      ChangeSize(LOWORD(lParam),HIWORD(lParam));
      break;

    case WM_KEYDOWN:                                 // ��Ӧ��������ѶϢ
      keys[wParam] = TRUE;
      KeyPress();
      SendMessage(hWnd, WM_PAINT, 0, 0L);
      break;

    case WM_KEYUP:                                   // ��Ӧ�ɿ�������ѶϢ
      keys[wParam] = FALSE;
      SendMessage(hWnd, WM_PAINT, 0, 0L);
      break;

    case WM_LBUTTONDOWN:                             // ��Ӧ����������ѶϢ
      mouseFlag = TRUE;
      GetCursorPos(&ptCurr);
      break;

    case WM_MOUSEMOVE:
      if(mouseFlag)
      {
        xRot = (((int)(short)LOWORD(lParam)) - ptCurr.x)*0.5;
        yRot = (((int)(short)HIWORD(lParam)) - ptCurr.y)*0.5;
        SendMessage(hWnd, WM_PAINT, 0, 0L);
      }
      break;

    case WM_LBUTTONUP:                               // ̧��������ѶϢ
      mouseFlag = FALSE;
      xRot = 0;
      yRot = 0;
      break;

    case WM_RBUTTONDOWN:                               // ̧��������ѶϢ
      GetCursorPos(&pt);
      TrackPopupMenu(hPopup, TPM_RIGHTBUTTON, pt.x, pt.y, (DWORD)NULL, hWnd, NULL);
      break;


    case WM_COMMAND:
      switch(wParam)
	  {
        case IDM_AUTO:
          SetTimer(hWnd, ID_TIMER, 200 ,timerProc);
          break;
        case IDM_STOP:
          KillTimer(hWnd,ID_TIMER);
          break;
        case IDM_BLACK:
          color[0] = 0.0f;
          color[1] = 0.0f;
          color[2] = 0.0f;
          break;
        case IDM_GRAY:
          color[0] = 0.5f;
          color[1] = 0.5f;
          color[2] = 0.5f;
          break;
        case IDM_SKYBLUE:
          color[0] = 0.3398f;
          color[1] = 0.9766f;
          color[2] = 0.9961f;
          break;
        case IDM_WHITE:
          color[0] = 1.0f;
          color[1] = 1.0f;
          color[2] = 1.0f;
          //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
          break;

        case IDC_Room1:
          //flag = false;
          if(flag4){
            flag4 = false;
          }
          else{
            flag4 = true;
          }
          SendMessage(hWnd, WM_PAINT, 0, 0L);
          break;

        case IDC_Room2:
          //flag = false;
          control = 2;
          SendMessage(hWnd, WM_PAINT, 0, 0L);
          break;

        case IDC_ON:
          projector = 1;
          break;

        case IDC_OFF:
          projector = 0;
          break;

        case IDC_RotateX1:
          xlookAt += lookStep;
          break;

        case IDC_RotateX2:
          xlookAt -= lookStep;
          break;

        case IDC_RotateY1:
          ylookAt += lookStep;
          break;

        case IDC_RotateY2:
          ylookAt -= lookStep;
          break;

        case IDC_RotateZ1:
          zlookAt += lookStep;
          break;

        case IDC_RotateZ2:
          zlookAt -= lookStep;
          break;

        case IDC_TranslateX1:
          xPosition -= moveStep;
          break;

        case IDC_TranslateX2:
          xPosition += moveStep;
          break;

        case IDC_TranslateY1:
          yPosition += moveStep;
          break;

        case IDC_TranslateY2:
          yPosition -= moveStep;
          break;

        case IDC_TranslateZ1:
          zPosition += moveStep;
          break;

        case IDC_TranslateZ2:
          zPosition -= moveStep;
          break;

        default:
          return DefWindowProc(hWnd,message,wParam,lParam);
	  }
	  SendMessage(hWnd, WM_PAINT, 0, 0L);
	  SetFocus(hWnd);
      break;

    case WM_DESTROY:                                 // �˳�����
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hWnd,message,wParam,lParam);

  }
  return DefWindowProc(hWnd,message,wParam,lParam);

}// ������̶���

//********************************************************************
//*  ���غ���                                                        *
//********************************************************************
//
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
  MSG msg;                                           // ������Ϣ

  if(MainWndCls())          return 1;                // ��������ע��

  MainWndMenu();                                     // ��ʾ������˵�

  if(MainWndCreate())       return 2;                // ����������

  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);                          // ת����Ϣ
    DispatchMessage(&msg);                           // �ַ���Ϣ
  }

  return (int)msg.wParam;
}// ���غ���


//********************************************************************
//*  OpenGL��ʼ�������¼�                                            *
//********************************************************************
//
GLvoid Init()
{
glBlendFunc(GL_SRC_ALPHA,GL_ONE);                       // ʹ�õ���
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			// ���ñ���ɫΪ��ɫ
glEnable(GL_TEXTURE_2D);
glClearDepth(1.0);					// �����Ȼ���
glDepthFunc(GL_LESS);					// ����ΪLESS
glEnable(GL_DEPTH_TEST);				// ��Ȼ������

glShadeModel(GL_SMOOTH);				// Enables Smooth Color Shading
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����Niceset
} //OpenGL��ʼ�������¼�

//********************************************************************
//*  ʹ�������Ŵ��ڵĴ�С�仯���仯�¼�����                          *
//********************************************************************
//
GLvoid ChangeSize(GLsizei width, GLsizei height)
{
    float ar = (float) (width-180) / (float) height;

    glViewport(0, 0, width-180, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity() ;
glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}// ʹ�������Ŵ��ڵĴ�С�仯���仯�¼�����
GLfloat position;
//********************************************************************
//*  ��ͼ�ν��л���(��Ⱦ)�¼�                                        *
//********************************************************************
//
GLvoid Draw3D()
{
    glClearColor(color[0], color[1], color[2], color[3]);
    if(!flag4){
       Draw3D1();
    }
    else if(flag4){
       Draw3D2();
    }
                           // ��������(˫����)
} //��ͼ�ν��л���(��Ⱦ)�¼�

GLvoid Draw3D1()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
gluLookAt(xlookAt,ylookAt,zlookAt,0, 0, 0, 0, 0, -1);
GLfloat light2_position[] = {-0.57f, -0.15f , -0.87f, 1.0f };
glColor3f( 0, 1, 0 );

glPushMatrix();

    //glDisable(GL_TEXTURE_2D);

    glTranslated(xPosition,yPosition+0.5,zPosition);
    //glTranslated(0, 0, -2.5);
    glRotated(xRot,1,0,0);
    glRotated(yRot,0,1,0);
    glRotated(zRot,0,0,1);
    glTranslated(0, -0.12, 0);
    //glRotated(90,1,0,0);
    //glRotated(30,0,0,1);

    glDisable(GL_TEXTURE_2D);
        //����
     glPushMatrix();
        glTranslated(0, -0.1, 0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        //ǽ1
        glBindTexture(GL_TEXTURE_2D, texShip);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, -1.0, -1.2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 2.7, -1.2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 2.7, -1.2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5,-1.0, -1.2);
        glEnd();

        //�ڻ�
        glBindTexture(GL_TEXTURE_2D, texSea);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, 0.3, -1.18);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, 1.5, -1.18);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 1.5, -1.18);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5,0.3, -1.18);
        glEnd();

        //ǽ2
        glBindTexture(GL_TEXTURE_2D, texShip);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, -1.0, 2.2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 2.7, 2.2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5, 2.7, -1.2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5, -1.0, -1.2);
        glEnd();
//        glBindTexture(GL_TEXTURE_2D, texShip);
//        glBegin(GL_QUADS);
//            glTexCoord2f(0.0f, 0.0f); glVertex3f(2.5, -1.0, 2.2);
//            glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5, 2.7, 2.2);
//            glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 2.7, -1.2);
//            glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5, -1.0, -1.2);
//        glEnd();

        glBindTexture(GL_TEXTURE_2D, texCarpet);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, -1.0, 2.2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5, -1.0, 2.2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5,-1.0, -1.2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5, -1.0, -1.2);
        glEnd();

        //����
        glBindTexture(GL_TEXTURE_2D, texSky);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.48, 0.0, 2.0);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.48, 1.3, 2.0);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.48, 1.3, 0.65);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.48, 0.0, 0.65);
        glEnd();

//        //��̺
//        glBindTexture(GL_TEXTURE_2D, texCarpet);
//        glBegin(GL_QUADS);
//            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, 0.9, 1.8);
//            glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5, 0.9, 1.8);
//            glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5,0.9, -0.8);
//            glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.9, -0.8);
//        glEnd();
        glDisable(GL_TEXTURE_2D);
     glPopMatrix();
    glPushMatrix();
    //����
      glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
      glTranslated(-0.57f, -0.15f , -0.87f);
      glDisable(GL_LIGHTING);
      glColor3f(1.0f, 1.0f, 0.0f);
      glutSolidSphere(0.05f, 50.0f, 50.0f);

    glPopMatrix();
    glPushMatrix();
      glEnable(GL_LIGHTING);
      glTranslated(0.4, -0.8, -0.46);

    //����
      glPushMatrix();
        //glRotated(-90, 0, 1, 0);
        glTranslated(0, 0, 0.15);
        glScaled(4.5, 1.5, 5);
        glutSolidCube(0.3);
      glPopMatrix();
    //������
      glPushMatrix();
        //glRotated(-90, 0, 1, 0);
        glTranslated(0, 0.155, -0.63);
        glScaled(4.5, 3, 0.5);
        glutSolidCube(0.3);
      glPopMatrix();

      //��ͷ
      glPushMatrix();
        glColor3f(0.5, 0, 0.5);
        glTranslated(0, 0.3, -0.5);
        glScaled(1, 0.3, 0.3);
        glutSolidSphere(0.3, 60, 60);
      glPopMatrix();

      glTranslated(0, 0, -0.6);
      //��ͷ��
      glPushMatrix();
        //glDisable(GL_LIGHTING);

        glTranslated(0.22, 0, 0);
        glPushMatrix();
          glColor3f(1, 1, 1);
          glTranslated(-1.2, 0.20, 0.17);
          glScaled(1.7, 0.2, 1.7);
          glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
          glTranslated(-0.93, -0.02, 0.17);
          glScaled(0.2, 1.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
          glTranslated(-1.47, -0.02, 0.17);
          glScaled(0.2, 1.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
          glTranslated(-1.2, -0.02, -0.10);
          glScaled(1.7, 1.5, 0.2);
          glutSolidCube(0.3);
        glPopMatrix();

        //���ӵ���
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0, 0.15);
          glScaled(1.5, 0.2, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //���������
        glPushMatrix();
          glTranslated(-1.4, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //�����Ҳ���
        glPushMatrix();
          glTranslated(-1.0, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //����ǰ��
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(1.5, 0.7, 0.2);
          glutSolidCube(0.3);
        glPopMatrix();

        //���Ӱ���
        glPushMatrix();
          glColor3f(0, 0, 0);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(0.5, 0.5, 0.5);
          glutSolidSphere(0.1, 60, 60);
        glPopMatrix();

        glTranslated(0, -0.21, 0);
        //������ӵ���
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0, 0.15);
          glScaled(1.5, 0.2, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //������������
        glPushMatrix();
          glTranslated(-1.4, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //��������Ҳ���
        glPushMatrix();
          glTranslated(-1.0, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //�������ǰ��
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(1.5, 0.7, 0.2);
          glutSolidCube(0.3);
        glPopMatrix();

        //������Ӱ���
        glPushMatrix();
          glColor3f(0, 0, 0);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(0.5, 0.5, 0.5);
          glutSolidSphere(0.1, 60, 60);
        glPopMatrix();
      glPopMatrix();

      glTranslated(2.2, 0, 0);
      glPushMatrix();
        //glDisable(GL_LIGHTING);
        glPushMatrix();
          glColor3f(1, 1, 1);
          glTranslated(-1.2, 0.20, 0.17);
          glScaled(1.7, 0.2, 1.7);
          glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
          glTranslated(-0.93, -0.02, 0.17);
          glScaled(0.2, 1.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
          glTranslated(-1.47, -0.02, 0.17);
          glScaled(0.2, 1.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        glPushMatrix();
          glTranslated(-1.2, -0.02, -0.10);
          glScaled(1.7, 1.5, 0.2);
          glutSolidCube(0.3);
        glPopMatrix();

        //���ӵ���
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0, 0.15);
          glScaled(1.5, 0.2, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //���������
        glPushMatrix();
          glTranslated(-1.4, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //�����Ҳ���
        glPushMatrix();
          glTranslated(-1.0, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //����ǰ��
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(1.5, 0.7, 0.2);
          glutSolidCube(0.3);
        glPopMatrix();

        //���Ӱ���
        glPushMatrix();
          glColor3f(0, 0, 0);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(0.5, 0.5, 0.5);
          glutSolidSphere(0.1, 60, 60);
        glPopMatrix();

        glTranslated(0, -0.21, 0);
        //������ӵ���
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0, 0.15);
          glScaled(1.5, 0.2, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //������������
        glPushMatrix();
          glTranslated(-1.4, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //��������Ҳ���
        glPushMatrix();
          glTranslated(-1.0, 0.08, 0.15);
          glScaled(0.2, 0.6, 1.5);
          glutSolidCube(0.3);
        glPopMatrix();

        //�������ǰ��
        glPushMatrix();
          glColor3f(0, 0, 1);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(1.5, 0.7, 0.2);
          glutSolidCube(0.3);
        glPopMatrix();

        //������Ӱ���
        glPushMatrix();
          glColor3f(0, 0, 0);
          glTranslated(-1.2, 0.07, 0.39);
          glScaled(0.5, 0.5, 0.5);
          glutSolidSphere(0.1, 60, 60);
        glPopMatrix();
      glPopMatrix();

      //��޹
      glPushMatrix();
        glColor3f(1, 0.5, 0.5);
        glTranslated(-1.3, 0.25, 0.3);
        glBegin(GL_QUAD_STRIP);
           R1 = 0.07;
           for(int i=0;i<n;i=i++){
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0.15, R1*sin(2*PI/n*i)-0.1);
           }
        glEnd();
      glPopMatrix();

      //��޹��1
      glPushMatrix();
        glColor3f(0, 1, 1);
        glTranslated(-1.3, 0.25, 0.3);
        glRotated(15,0, 0, 1);
        glBegin(GL_QUAD_STRIP);
           R1 = 0.01;
           for(int i=0;i<n;i=i++){
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0.25, R1*sin(2*PI/n*i)-0.1);
           }
        glEnd();
      glPopMatrix();

      //��޹��2
      glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslated(-1.3, 0.30, 0.3);
        glRotated(-15,0, 0, 1);
        glBegin(GL_QUAD_STRIP);
           R1 = 0.01;
           for(int i=0;i<n;i=i++){
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0.25, R1*sin(2*PI/n*i)-0.1);
           }
        glEnd();
      glPopMatrix();

      //��޹��3
      glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslated(-1.3, 0.25, 0.3);
        glRotated(30,0, 0, 1);
        glBegin(GL_QUAD_STRIP);
           R1 = 0.01;
           for(int i=0;i<n;i=i++){
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
              glVertex3f(R1*cos(2*PI/n*i)+0.1, 0.25, R1*sin(2*PI/n*i)-0.1);
           }
        glEnd();
      glPopMatrix();
    glPopMatrix();

    //������
    glPushMatrix();
      glColor3f(1, 1, 1);
      //glTranslated(-1.45, 1.2, 1.34);
      glPushMatrix();
        glTranslated(-1.45, 1.2, 1.34);
        glScaled(0.25, 0.25, 4.6);
        glutSolidCube(0.3);
      glPopMatrix();
      glPushMatrix();
        glTranslated(-1.45, -0.1, 1.34);
        glScaled(0.25, 0.25, 4.6);
        glutSolidCube(0.3);
      glPopMatrix();
      glPushMatrix();
        glTranslated(-1.45, 0.55, 1.34);
        glScaled(0.25, 4.6, 0.25);
        glutSolidCube(0.3);
      glPopMatrix();

      glPushMatrix();
        glTranslated(-1.45, 0.55, 2.0);
        glScaled(0.25, 4.6, 0.25);
        glutSolidCube(0.3);
      glPopMatrix();

      glPushMatrix();
        glTranslated(-1.45, 0.55, 0.67);
        glScaled(0.25, 4.6, 0.25);
        glutSolidCube(0.3);
      glPopMatrix();

    glPopMatrix();

    //��ױ̨
    glPushMatrix();
      glTranslated(-1.0, -0.28, 1.3);
      glScaled(0.8, 0.8, 0.8);

      //������
      glPushMatrix();
        glRotated(90,1,0,0);
        glRotated(90,0,0,1);
        glScalef (2.0, 1.4, 0.1);
        glColor3f( 0, 1, 0 );
        glutSolidCube(0.8);

      glPopMatrix();
      //glRotated(-90,0,1,0);
      //������1
      glPushMatrix();
        glRotated(-90,0,1,0);
        glTranslated(-0.6, -0.5, 0.4);
        glColor3f( 0, 1, 0 );
        glScalef(0.1, 1.2, 0.1);
        glutSolidCube(0.8);
      glPopMatrix();
      //������2
      glPushMatrix();

        glRotated(-90,0,1,0);
        glTranslated(-0.6, -0.5, -0.4);
        glColor3f( 0, 1, 0 );
        glScalef(0.1, 1.2, 0.1);
        glutSolidCube(0.8);
      glPopMatrix();
      //������3
      glPushMatrix();
        glRotated(-90,0,1,0);
        glTranslated(0.6, -0.5, 0.4);
        glColor3f( 0, 1, 0 );
        glScalef(0.1, 1.2, 0.1);
        glutSolidCube(0.8);
      glPopMatrix();
//������4
      glPushMatrix();
        glRotated(-90,0,1,0);
        glTranslated(0.6, -0.5, -0.4);
        glColor3f( 0, 1, 0 );
        glScalef(0.1, 1.2, 0.1);
        glutSolidCube(0.8);
      glPopMatrix();

      glTranslated(0.5, 0, 0.2);
     //������1
      glPushMatrix();
        glTranslated(0, -0.2, -0.5);
        glRotated(-90,0,1,0);
        glRotated(-180,0,1,0);
        glTranslated(0.23, 0.0, -0.18);
        glTranslated(-0.6, -0.5, 0.5);
        glColor3f( 0, 1, 0 );
        glScalef(0.2, 1.5, 0.2);
        glutSolidCube(0.4);
      glPopMatrix();
//������2
      glPushMatrix();
        glTranslated(0, -0.2, -0.5);
        glRotated(-90,0,1,0);
        glRotated(-180,0,1,0);
        glTranslated(0.23, 0.0, 0.18);
        glTranslated(-0.6, -0.5, -0.4);
        glColor3f( 0, 1, 0 );
        glScalef(0.2, 1.5, 0.2);
        glutSolidCube(0.4);
      glPopMatrix();
//������3
      glPushMatrix();
        glTranslated(0, -0.2, -0.5);
        glRotated(-90,0,1,0);
        glRotated(-180,0,1,0);
        glTranslated(-0.46, 0.0, -0.2);
        glTranslated(0.6, -0.5, 0.5);
        glColor3f( 0, 1, 0 );
        glScalef(0.2, 1.5, 0.2);
        glutSolidCube(0.4);
      glPopMatrix();
//������4
      glPushMatrix();
        glTranslated(0, -0.2, -0.5);
        glRotated(-90,0,1,0);
        glRotated(-180,0,1,0);
        glTranslated(-0.46, 0.0, 0.19);
        glTranslated(0.6, -0.5, -0.4);
        glColor3f( 0, 1, 0 );
        glScalef(0.2, 1.5, 0.2);
        glutSolidCube(0.4);
      glPopMatrix();
//������
      glPushMatrix();
        glTranslated(0, -0.2, -0.5);
        glRotated(-180,0,1,0);
        glRotated(90,1,0,0);
        glRotated(90,0,0,1);
        glTranslated(-0.1, 0, 0.2);
        glColor3f( 0, 1, 0 );
        glScalef (0.8, 0.8, 0.1);
    //glColor3f( 1, 1, 0 );
        glutSolidCube(0.8);

      glPopMatrix();
//�α�
      glPushMatrix();
        glTranslated(0, -0.2, -0.5);
        glRotated(-180,0,1,0);
        glRotated(-90,0,1,0);
        glTranslated(-0.1, 0.08, 0.36);
        glColor3f( 0, 1, 0 );
        glScalef (0.8, 0.8, 0.1);
        glutSolidCube(0.8);
      glPopMatrix();

    glPopMatrix();


     //̨�Ƶ���������
     glPushMatrix();
        glTranslated(-0.6, -0.45, -0.85);
        glColor3f(1, 1, 1);
        glutSolidCube(0.2);
        glTranslated(0, 0.27, 0);
        glScaled(0.2, 0.2, 0.2);
        glutWireIcosahedron();
        GLfloat mat_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat mat_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
     glPopMatrix();

     //�¹�
     glPushMatrix();
       //glTranslated(-1.2, -1.0, -0.6);
       glPushMatrix();
         glTranslated(-1.2, 0.9, -0.42);
         glScaled(1.8, 0.2, 4.8);
         glutSolidCube(0.3);
       glPopMatrix();
       glPushMatrix();
         glTranslated(-1.2, -0.1, -1.12);
         glScaled(1.8, 6.6, 0.2);
         glutSolidCube(0.3);

       glPopMatrix();
       glPushMatrix();
         glTranslated(-1.2, -0.1, 0.27);
         glScaled(1.8, 6.6, 0.2);
         glutSolidCube(0.3);
       glPopMatrix();

       //�ҹ���
       glPushMatrix();
         glTranslated(-0.9, -0.1, -0.75);
         glScaled(0.2, 6.6, 2.2);
         glutSolidCube(0.3);
       glPopMatrix();

       //�����
       glPushMatrix();
         glColor3f(0, 0, 1);
         glTranslated(-0.9, -0.1, -0.1);
         glScaled(0.2, 6.6, 2.2);
         glutSolidCube(0.3);
       glPopMatrix();

       glPushMatrix();
         glColor3f(0, 0, 0);
         glTranslated(-0.8, 0.0, -0.5);
         glScaled(0.5, 0.5, 0.5);
         glutSolidSphere(0.1, 60, 60);
       glPopMatrix();

       glPushMatrix();
         glColor3f(0, 0, 0);
         glTranslated(-0.8, 0.0, -0.3);
         glScaled(0.5, 0.5, 0.5);
         glutSolidSphere(0.1, 60, 60);
       glPopMatrix();
     glPopMatrix();

     //�ʼǱ�����
     glPushMatrix();

       glColor3f(0.996, 0.83, 0);
       glPushMatrix();
         glTranslated(-1.3, -0.08, 1.1);
         glRotated(15, 0, 0, 1);
         glScaled(0.1, 1.0, 1.5);
         glutSolidCube(0.3);
         glTranslated(0.22, 0, 0);
         glColor3f(0, 0, 0);
         glutSolidCube(0.27);
       glPopMatrix();
       glPushMatrix();
         glColor3f(0.996, 0.83, 0);
         glTranslated(-1.15, -0.22, 1.1);
         glScaled(1.0,0.1,  1.5);
         glutSolidCube(0.3);
       glPopMatrix();
     glPopMatrix();

     //�¼�����
     glPushMatrix();
     glTranslated(0.8, 0, -0.8);
     glPushMatrix();
       glTranslated(1.2, -0.1, 0.2);
       glColor3f(1, 0, 0);
       glScaled(0.3, 3.0, 0.3);
       R1 = 0.6;
       R2 = 0.6;
       glutSolidSphere(0.3, 60, 60);
       glTranslated(-0.1, -0.3, 0.15);
       glBegin(GL_QUAD_STRIP);
          for(int i=0;i<n;i=i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
             glVertex3f(R2*cos(2*PI/n*i)+0.1, 0.03, R2*sin(2*PI/n*i)-0.1);
          }
       glEnd();
       glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
             glVertex3f(R2*cos(2*PI/n*i)+0.1, 0.03, R1*sin(2*PI/n*i)-0.1);
          }
       glEnd();
       glColor3f(0, 0, 0);
       glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1,0, R1*sin(2*PI/n*i)-0.1);

          }
       glEnd();
       glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1,0.03, R1*sin(2*PI/n*i)-0.1);
          }
       glEnd();
     glPopMatrix();

     glPushMatrix();
       glTranslated(1.07, 0.4, 0.2);
       glRotated(30, 0, 0, 1);
       glColor3f(1, 0, 0);
       glScaled(0.2, 1.2, 0.2);
       glutSolidSphere(0.2, 60, 60);
       glTranslated(-1.3, -0.4, 0);
       glutSolidSphere(0.2, 60, 60);
     glPopMatrix();

     glPushMatrix();
       glTranslated(1.27, 0.4, 0.2);
       glRotated(-30, 0, 0, 1);
       glColor3f(1, 0, 0);
       glScaled(0.2, 1.2, 0.2);
       glutSolidSphere(0.2, 60, 60);
       glTranslated(1.5, -0.4, 0);
       glutSolidSphere(0.2, 60, 60);
     glPopMatrix();

     glPopMatrix();

     //ͶӰ��
     glPushMatrix();
       glColor3f(1, 1, 1);
       glTranslated(0.4, 1.5, -1.1);
       glScaled(5, 0.4, 0.4);
       glutSolidCube(0.3);
     glPopMatrix();

     if(projector == 1){
        Draw3D3();
     }

     glPushMatrix();
       glColor3f(0, 1, 1);
       glRotated(90, 1, 0, 0);
       glTranslated(0.5, 1.4, 0.8);
       glutSolidTorus(0.15, 0.25, 60, 60);
     glPopMatrix();
glPopMatrix();

glPushMatrix();
    glTranslated(xPosition_person,yPosition_person+0.1,zPosition_person-1);
//    glTranslated(xPosition_person,yPosition_person+0.1,zPosition_person-5)
    glTranslated(0, 0, zPosition_person);
    //glRotated(backRot, 0, 1, 0);
    glRotated(xRot,1,0,0);
    glRotated(yRot,0,1,0);
    glRotated(zRot,0,0,1);
    glTranslated(1.5, 0.4, 1.5);
 // glEnable(GL_LIGHTING);
  //glRotated(90, 0, 1, 0);
  glColor3f(1, 0, 0);
  glRotated(backRot, 0, 1, 0);
  //ͷ�Ͳ���
  glScaled(0.5, 0.5, 0.5);
  glPushMatrix();
    glutSolidCube(0.5);
    glTranslated(0, -0.2, 0);
    glColor3f(1, 1, 1);
    glScaled(1, 2.2, 1);
    glutSolidCube(0.2);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0.13, 0.08, 0.26);
    glScaled(0.5, 0.5, 0.1);
    glutSolidCube(0.2);
  glPopMatrix();

  glPushMatrix();
    glTranslated(0, 0.08, 0.26);
    glScaled(1.0, 0.1, 0.1);
    glutSolidCube(0.2);
  glPopMatrix();

  glPushMatrix();
    glTranslated(0, -0.12, 0.26);
    glScaled(1.0, 0.3, 0.1);
    glutSolidCube(0.2);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(-0.12, 0.08, 0.26);
    glScaled(0.5, 0.5, 0.1);
    glutSolidCube(0.2);
  glPopMatrix();
  //���
  glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(0, -0.50, 0);
    glScaled(1.8, 0.4, 0.4);
    glutSolidCube(0.6);
  glPopMatrix();

  //�첲������
  glPushMatrix();
    glTranslated(-0.4, -1.05, 0);
    glScaled(0.3, 1.4, 0.3);
    glutSolidCube(0.6);
    glTranslated(2.7, 0, 0);
    glutSolidCube(0.6);
    glTranslated(-1.38, 0, 0);
    glColor3f(1, 0, 0);
    glScaled(3.3, 1.2, 1.2);
    glutSolidCube(0.6);
  glPopMatrix();

//  //����
  glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslated(-0.18, -1.8, 0);
    glRotated(legL, 1, 0, 0);
    glScaled(0.34, 1.4, 0.34);
    glutSolidCube(0.6);
  glPopMatrix();
  //����
  glPushMatrix();
    glTranslated(0.18, -1.8, 0);
    glRotated(legR, 1, 0, 0);
    glScaled(0.34, 1.4, 0.34);
    glutSolidCube(0.6);
  glPopMatrix();

glPopMatrix();
SwapBuffers(hDC);
glClearColor(0,0,0,1);
glEnable(GL_DEPTH_TEST);

GLfloat light0_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light0_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat light0_position[] = { 5.0f, 5.0f, 1.0f, 0.0f };

GLfloat light2_diffuse[] = {1.0f,1.0f,1.0f,1.0f};
//GLfloat light2_ambient[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat light2_ambient[] = {1.0f,0.5f,0.5f,1.0f};

GLfloat light1_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light1_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light1_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat light1_position[] = { 2.0f, -1.0f, 5.0f, 0.0f };

GLfloat spot_direction[] = {0.0, -1.0, 0.0};

GLfloat mat_specular[]   = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat high_shininess[] = { 100.0f };
//GLfloat spot_direction[]=  { 1.0f, 1.0f, -1.0f};

glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

glLightfv(GL_LIGHT2,GL_DIFFUSE,light2_diffuse);
glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, spot_direction);
glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
//glLightfv(GL_LIGHT2,GL_AMBIENT,light2_ambient);

glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glEnable(GL_LIGHT2);
glEnable(GL_LIGHTING);

SetupRC();

                           // ��������(˫����)
} //��ͼ�ν��л���(��Ⱦ)�¼�

GLvoid Draw3D3()
{
    glPushMatrix();
       glColor3f(1, 1, 1);
       glBegin(GL_POLYGON);
         glVertex3f(-0.3, 0.3, -1.15);
         glVertex3f(-0.3, 1.6, -1.15);
         glVertex3f(1.1, 1.6, -1.15);
         glVertex3f(1.1,0.3, -1.15);
       glEnd();
     glPopMatrix();
}

GLvoid Draw3D2()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
gluLookAt(xlookAt, ylookAt, zlookAt,0, 0, 0, 0, 0, -1);
GLfloat light2_position[] = { -0.57f, 0.36f , 0.3f, 1.0f };

//glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
//glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    glTranslated(0, 0, -1);
    glTranslated(xPosition,yPosition,zPosition+1);
    glRotated(xRot,1,0,0);
    glRotated(yRot,0,1,0);
    glRotated(zRot,0,0,1);
    glTranslated(0, -0.1, 0);
glPushMatrix();
    //����
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glTranslated(-0.57f, 0.36f , 0.3f);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.05f, 50.0f, 50.0f);
	//glEnable(GL_LIGHTING);
glPopMatrix();
glColor3f(0, 1, 0 );
glEnable(GL_LIGHTING);
    //������1
glPushMatrix();
    glRotated(-30,0,1,0);
    glTranslated(-0.6, -0.5, 0.4);
    glColor3f( 0, 1, 0 );
    glScalef(0.1, 1.2, 0.1);
    glutSolidCube(0.8);
glPopMatrix();
//������2
glPushMatrix();

    glRotated(-30,0,1,0);
    glTranslated(-0.6, -0.5, -0.4);
    glColor3f( 0, 1, 0 );
    glScalef(0.1, 1.2, 0.1);
    glutSolidCube(0.8);
glPopMatrix();
//������3
glPushMatrix();
    glRotated(-30,0,1,0);
    glTranslated(0.6, -0.5, 0.4);
    glColor3f( 0, 1, 0 );
    glScalef(0.1, 1.2, 0.1);
    glutSolidCube(0.8);
glPopMatrix();
//������4
glPushMatrix();
    glRotated(-30,0,1,0);
    //glRotated(10,1,0,0);
    glTranslated(0.6, -0.5, -0.4);
    glColor3f( 0, 1, 0 );
    glScalef(0.1, 1.2, 0.1);
    glutSolidCube(0.8);
glPopMatrix();

//������1
glPushMatrix();
    glTranslated(0, -0.2, -0.5);
    glRotated(-30,0,1,0);
    glRotated(-180,0,1,0);
    glTranslated(0.23, 0.0, -0.18);
    glTranslated(-0.6, -0.5, 0.5);
    glColor3f( 0, 1, 0 );
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(0.4);
glPopMatrix();
//������2
glPushMatrix();
    glTranslated(0, -0.2, -0.5);
    glRotated(-30,0,1,0);
    glRotated(-180,0,1,0);
    glTranslated(0.23, 0.0, 0.18);
    glTranslated(-0.6, -0.5, -0.4);
    glColor3f( 0, 1, 0 );
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(0.4);
glPopMatrix();
//������3
glPushMatrix();
    glTranslated(0, -0.2, -0.5);
    glRotated(-30,0,1,0);
    glRotated(-180,0,1,0);
    glTranslated(-0.46, 0.0, -0.2);
    glTranslated(0.6, -0.5, 0.5);
    glColor3f( 0, 1, 0 );
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(0.4);
glPopMatrix();
//������4
glPushMatrix();
    glTranslated(0, -0.2, -0.5);
    glRotated(-30,0,1,0);
    glRotated(-180,0,1,0);
    glTranslated(-0.46, 0.0, 0.19);
    glTranslated(0.6, -0.5, -0.4);
    glColor3f( 0, 1, 0 );
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(0.4);
glPopMatrix();
//������
glPushMatrix();
    glTranslated(0, -0.2, -0.5);
    glRotated(-180,0,1,0);
    glRotated(90,1,0,0);
    glRotated(30,0,0,1);
    glTranslated(-0.1, 0, 0.2);
    glColor3f( 0, 1, 0 );
    glScalef (0.8, 0.8, 0.1);
    //glColor3f( 1, 1, 0 );
    glutSolidCube(0.8);

glPopMatrix();
//�α�
glPushMatrix();
    glTranslated(0, -0.2, -0.5);
    glRotated(-180,0,1,0);
    glRotated(-30,0,1,0);
    glTranslated(-0.1, 0.08, 0.36);
    glColor3f( 0, 1, 0 );
    glScalef (0.8, 0.8, 0.1);
    glutSolidCube(0.8);

glPopMatrix();
//���������
glPushMatrix();
    glTranslated(0, 0.05, 0.5);
    R1 = 0.2;
    R2 = 0.4;
    glColor3f( 0, 1, 1 );
    glScaled(0.5, 0.5, 0.5);
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<n;i=i++){
           glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
           glVertex3f(R2*cos(2*PI/n*i)+0.1, 0.1, R2*sin(2*PI/n*i)-0.1);
        }
    glEnd();
    glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
          }
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1,0, R1*sin(2*PI/n*i)-0.1);
          }
    glEnd();
    glTranslated(0, -0.05, -0.35);
    glTranslated(0.07, 0.2, 0.3);
    glColor3f( 0, 0, 1 );
    glutSolidTeapot(0.2);

glPopMatrix();

//̨�Ƶ���������
glPushMatrix();
    glTranslated(-0.6, 0.15, 0.2);
    glColor3f(1, 1, 1);
    glutSolidCube(0.2);
    glTranslated(0, 0.27, 0);
    glScaled(0.2, 0.2, 0.2);
    glutWireIcosahedron();
    GLfloat mat_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
glPopMatrix();

//�¼�����
glPushMatrix();
    glTranslated(1.2, -0.1, 0.2);
    glColor3f(1, 0, 0);
    glScaled(0.3, 3.0, 0.3);
    R1 = 0.6;
    R2 = 0.6;
    glutSolidSphere(0.3, 60, 60);
    glTranslated(-0.1, -0.3, 0.15);
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<n;i=i++){
           glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
           glVertex3f(R2*cos(2*PI/n*i)+0.1, 0.03, R2*sin(2*PI/n*i)-0.1);
        }
    glEnd();
    glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1, 0, R1*sin(2*PI/n*i)-0.1);
             glVertex3f(R2*cos(2*PI/n*i)+0.1, 0.03, R1*sin(2*PI/n*i)-0.1);
          }
    glEnd();
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1,0, R1*sin(2*PI/n*i)-0.1);

          }
    glEnd();
    glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex3f(R1*cos(2*PI/n*i)+0.1,0.03, R1*sin(2*PI/n*i)-0.1);
          }
    glEnd();
glPopMatrix();

glPushMatrix();
    glTranslated(1.07, 0.4, 0.2);
    glRotated(30, 0, 0, 1);
    glColor3f(1, 0, 0);
    glScaled(0.2, 1.2, 0.2);
    glutSolidSphere(0.2, 60, 60);
    glTranslated(-1.3, -0.4, 0);
    glutSolidSphere(0.2, 60, 60);

glPopMatrix();

glPushMatrix();
    glTranslated(1.27, 0.4, 0.2);
    glRotated(-30, 0, 0, 1);
    glColor3f(1, 0, 0);
    glScaled(0.2, 1.2, 0.2);
    glutSolidSphere(0.2, 60, 60);
    glTranslated(1.5, -0.4, 0);
    glutSolidSphere(0.2, 60, 60);

glPopMatrix();
glPopMatrix();

//�����漰ǽ�ڵذ������
glPushMatrix();
    //glDisable(GL_TEXTURE_2D);
    glTranslated(0, 0, -1);
    glTranslated(xPosition,yPosition,zPosition+1);
    glRotated(xRot,1,0,0);
    glRotated(yRot,0,1,0);
    glRotated(zRot,0,0,1);
    glTranslated(0, -0.12, 0);
    glRotated(90,1,0,0);
    glRotated(30,0,0,1);
    glPushMatrix();
        glRotated(-90, 1, 0, 0);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texShip);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, -1.0, -1.2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 3.5, -1.2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 3.5, -1.2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5,-1.0, -1.2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texSea);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, 0.3, -1.18);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, 1.5, -1.18);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 1.5, -1.18);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5,0.3, -1.18);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texShip);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, -1.0, 2.2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5, 3.5, 2.2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5, 3.5, -1.2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5, -1.0, -1.2);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texFloor);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5, -1.0, 2.2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5, -1.0, 2.2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5,-1.0, -1.2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5, -1.0, -1.2);
        glEnd();


        glBindTexture(GL_TEXTURE_2D, texDoor);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.45, -1.0, 1.8);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.45, 2.2, 1.8);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.45, 2.2, 0.3);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.45, -1.0, 0.3);
        glEnd();
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glScalef (2.0, 1.4, 0.1);
    glColor3f( 0, 1, 0 );
    glutSolidCube(0.8);

glPopMatrix();

SwapBuffers(hDC);                              // ��������(˫����)

glClearColor(0,0,0,1);
glEnable(GL_DEPTH_TEST);

GLfloat light0_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light0_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat light0_position[] = { -5.0f, 5.0f, 1.0f, 0.0f };

GLfloat light2_diffuse[] = {1.0f,1.0f,1.0f,1.0f};
//GLfloat light2_ambient[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat light2_ambient[] = {1.0f,0.5f,0.5f,1.0f};


GLfloat light1_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light1_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light1_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat light1_position[] = { -5.0f, -3.0f, -10.0f, 0.0f };

GLfloat spot_direction[] = {0.0, -1.0, 0.0};

GLfloat mat_specular[]   = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat high_shininess[] = { 100.0f };
//GLfloat spot_direction[]=  { 1.0f, 1.0f, -1.0f};

glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

//glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
//glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

glLightfv(GL_LIGHT2,GL_DIFFUSE,light2_diffuse);
glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, spot_direction);
glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
//glLightfv(GL_LIGHT2,GL_AMBIENT,light2_ambient);

glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHT0);
//glEnable(GL_LIGHT1);
glEnable(GL_LIGHT2);
glEnable(GL_LIGHTING);

SetupRC();
} //��ͼ�ν��л���(��Ⱦ)�¼�
void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    texFloor = load_texture("data\\floor0.bmp");  //��������
    texShip = load_texture("data\\wall1.bmp");
    texSea = load_texture("data\\ocean.bmp");
    texCarpet = load_texture("data\\carpet.bmp");
    texDoor = load_texture("data\\door.bmp");
    texSky = load_texture("data\\sky.bmp");

}

//********************************************************************
//*  ���̿���ͼ���¼�����                                            *
//********************************************************************
//
GLuint KeyPress()
{
  if (keys[VK_UP])                                   // ���ϼ�ͷ��
    xRot -= rotStep;

  if (keys[VK_DOWN])                                 // ���¼�ͷ��
    xRot += rotStep;

  if (keys[VK_RIGHT]){                               // ���Ҽ�ͷ��
    yRot += rotStep;
  }

  if (keys[VK_LEFT])                                 // �����ͷ��
    yRot -= rotStep;

  if (keys[VK_HOME])                                 // ��HOME��
    zRot += rotStep;

  if (keys[VK_END])                                  // ��END��
    zRot -= rotStep;

  if (keys['A'])                                     // ��A��
    xPosition -= moveStep;

  if (keys['D'])                                     // ��D��
    xPosition += moveStep;

  if (keys['W'])                                     // ��W��
    yPosition += moveStep;

  if (keys['S'])                                     // ��S��
    yPosition -= moveStep;

  if (keys['Q'])                                     // ��Q��
    zPosition -= moveStep;

  if (keys['E'])                                     // ��E��
    zPosition += moveStep;

  if (keys[VK_ESCAPE])                               // ��ESC��
    SendMessage(hWnd,WM_DESTROY,0,0);

  return 0;
} // ���̿���ͼ���¼�����

//********************************************************************
//*  ��ʱ����������                                          *
//********************************************************************
//
GLvoid CALLBACK timerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{

    glEnable(GL_TEXTURE_2D);
    //ǰ��
    if(zPosition_person <= 0.9 && !flag2){
        if(legR < 0 && legL > 0){
            legR += paceStep;
            legL -= paceStep;
        }
        else{
            legR -= paceStep;
            legL += paceStep;
        }
        zPosition_person += moveStep;
    }
    if(zPosition_person > 0.9 && !flag3){
        backRot += 180.0;
        flag3 = true;
        flag2 = true;
    }
    //����
    if(zPosition_person >= 0 && flag2){
        if(legR < 0 && legL > 0){
            legR += paceStep;
            legL -= paceStep;
        }
        else{
            legR -= paceStep;
            legL += paceStep;
        }
        zPosition_person -= moveStep;
    }
    if(zPosition_person < 0 && flag3){
        backRot -= 180.0;
        flag3 = false;
        flag2 = false;
    }
    SendMessage(hWnd, WM_PAINT, 0, 0L);
}

/********************************************************************/
/*  ������˵����庯������                                          */
/********************************************************************/
//
GLuint MainWndMenu()
{
  hMenuMain = CreateMenu();
  hPopup = CreatePopupMenu();
  AppendMenu(hPopup,MF_STRING,IDM_AUTO,TEXT("Walk"));
  AppendMenu(hPopup,MF_STRING,IDM_STOP,TEXT("Stop"));
  AppendMenu(hPopup,MF_SEPARATOR,0,NULL);
  AppendMenu(hPopup,MF_STRING,IDM_BLACK,TEXT("Black"));
  AppendMenu(hPopup,MF_STRING,IDM_GRAY,TEXT("Gray"));
   AppendMenu(hPopup,MF_STRING,IDM_SKYBLUE,TEXT("SkyBlue"));
  AppendMenu(hPopup,MF_STRING,IDM_WHITE,TEXT("White"));

  AppendMenu(hMenuMain,MF_POPUP,(int)hPopup,TEXT("CONTROL"));

  return 0;
} // ������˵����庯��

/********************************************************************/
/*  ��������ؼ���������                                            */
/********************************************************************/
int commandBtns(HWND hWndParent)
{
  int diff = 1210;
  hCmdBtns = CreateWindowEx((DWORD)NULL,
                               "BUTTON",
                               "",
                               WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
                               diff+0,0,180,600,
                               hWndParent,
                               (HMENU)IDC_FRAME,
                               hInstance,
                               NULL);
  if(!hCmdBtns) return 1;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "x-",
                       WS_CHILD|WS_VISIBLE,
                       diff+20,100,42,32,
                       hWndParent,
                       (HMENU)IDC_RotateX1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 2;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "x+",
                       WS_CHILD|WS_VISIBLE,
                       diff+120,100,42,32,
                       hWndParent,
                       (HMENU)IDC_RotateX2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 3;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "y+",
                       WS_CHILD|WS_VISIBLE,
                       diff+72,60,42,32,
                       hWndParent,
                       (HMENU)IDC_RotateY1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 4;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "y-",
                       WS_CHILD|WS_VISIBLE,
                       diff+72,140,42,32,
                       hWndParent,
                       (HMENU)IDC_RotateY2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 5;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "z+",
                       WS_CHILD|WS_VISIBLE,
                       diff+120,60,42,32,
                       hWndParent,
                       (HMENU)IDC_RotateZ1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 6;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "z-",
                       WS_CHILD|WS_VISIBLE,
                       diff+20,140,42,32,
                       hWndParent,
                       (HMENU)IDC_RotateZ2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 7;

//  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
//                       "BUTTON",
//                       "Room2",
//                       WS_CHILD|WS_VISIBLE,
//                       diff+100,180,60,32,
//                       hWndParent,
//                       (HMENU)IDC_Room2,
//                       hInstance,
//                       NULL);
//  if(!hCmdBtns) return 17;

    hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "Change",
                       WS_CHILD|WS_VISIBLE,
                       diff+60,180,60,32,
                       hWndParent,
                       (HMENU)IDC_Room1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 16;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "OFF",
                       WS_CHILD|WS_VISIBLE,
                       diff+100,220,60,32,
                       hWndParent,
                       (HMENU)IDC_OFF,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 18;

    hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "ON",
                       WS_CHILD|WS_VISIBLE,
                       diff+20,220,60,32,
                       hWndParent,
                       (HMENU)IDC_ON,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 19;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ǩ�ؼ�
                       "STATIC",
                       "LootAt Control:",
                       WS_CHILD|WS_VISIBLE,
                       diff+8,20,120,32,
                       hWndParent,
                       (HMENU)IDC_RotateZ2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 8;

    hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ǩ�ؼ�
                       "STATIC",
                       "Translated Control:",
                       WS_CHILD|WS_VISIBLE,
                       diff+8,260,160,32,
                       hWndParent,
                       (HMENU)IDC_RotateZ2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 9;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "<<",
                       WS_CHILD|WS_VISIBLE,
                       diff+20,340,42,32,
                       hWndParent,
                       (HMENU)IDC_TranslateX1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 10;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       ">>",
                       WS_CHILD|WS_VISIBLE,
                       diff+120,340,42,32,
                       hWndParent,
                       (HMENU)IDC_TranslateX2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 11;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       TEXT("UP"),
                       WS_CHILD|WS_VISIBLE,
                       diff+72,300,42,32,
                       hWndParent,
                       (HMENU)IDC_TranslateY1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 12;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "DN",
                       WS_CHILD|WS_VISIBLE,
                       diff+72,380,42,32,
                       hWndParent,
                       (HMENU)IDC_TranslateY2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 13;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "ZI",
                       WS_CHILD|WS_VISIBLE,
                       diff+120,300,42,32,
                       hWndParent,
                       (HMENU)IDC_TranslateZ1,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 14;

  hCmdBtns = CreateWindowEx((DWORD)NULL,                 // ������ť�ؼ�
                       "BUTTON",
                       "ZO",
                       WS_CHILD|WS_VISIBLE,
                       diff+20,300,42,32,
                       hWndParent,
                       (HMENU)IDC_TranslateZ2,
                       hInstance,
                       NULL);
  if(!hCmdBtns) return 15;

  return 0;
}

// ����power_of_two�����ж�һ�������ǲ���2����������
int power_of_two(int n)
{
    if( n <= 0 )
        return 0;
    return (n & (n-1)) == 0;
}

/* ����load_texture
* ��ȡһ��BMP�ļ���Ϊ����
* ���ʧ�ܣ�����0������ɹ�������������
*/
GLuint load_texture(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID=0, texture_ID = 0;

    // ���ļ������ʧ�ܣ�����
    FILE* pFile = fopen(file_name, "rb");
    if( pFile == 0 )
        return 0;

    // ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);

    // ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
    {
        GLint line_bytes = width * 3;
        while( line_bytes % 4 != 0 )
            ++line_bytes;
        total_bytes = line_bytes * height;
    }

    // �����������ֽ��������ڴ�
    pixels = (GLubyte*)malloc(total_bytes);
    if( pixels == 0 )
    {
        fclose(pFile);
        return 0;
    }

    // ��ȡ��������
    if( fread(pixels, total_bytes, 1, pFile) <= 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    // �Ծ;ɰ汾�ļ��ݣ����ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
    // ��ͼ���߳�����OpenGL�涨�����ֵ��Ҳ����
    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        if( !power_of_two(width) || !power_of_two(height) || width > max || height > max )
        {
            const GLint new_width = 256;
            const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;
            // ����ÿ����Ҫ���ֽ��������ֽ���
            new_line_bytes = new_width * 3;
            while( new_line_bytes % 4 != 0 )
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;
            // �����ڴ�
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if( new_pixels == 0 )
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }
            // ������������
            gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE, pixels,new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

            // �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
            free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }
    // ����һ���µ�������
    glGenTextures(1, &texture_ID);
    if( texture_ID == 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    // ���µ������������������������
    // �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
    GLint lastTextureID=last_texture_ID;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,0x80E0, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������
    free(pixels);
    return texture_ID;
}

