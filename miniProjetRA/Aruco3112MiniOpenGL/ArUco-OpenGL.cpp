//
//  ArUco-OpenGL.cpp
//
//  Created by Jean-Marie Normand on 28/02/13.
//  Copyright (c) 2013 Centrale Nantes. All rights reserved.
//


#include "ArUco-OpenGL.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\calib3d.hpp>

// Constructor
ArUco::ArUco(string intrinFileName, float markerSize) {
   // Initializing attributes
   m_IntrinsicFile= intrinFileName;
   m_MarkerSize   = markerSize;
   // read camera parameters if passed
   m_CameraParams.readFromXMLFile(intrinFileName);
  
}

// Destructor
ArUco::~ArUco() {}

void ArUco::resizeCameraParams(cv::Size newSize) {
	m_CameraParams.resize(newSize);
}

// Detect marker and draw things
void ArUco::doWork(Mat inputImg) {
   m_InputImage   = inputImg;
   m_GlWindowSize = m_InputImage.size();
   m_CameraParams.resize(m_InputImage.size());
   resize(m_GlWindowSize.width, m_GlWindowSize.height);
}

// Draw axis function
void ArUco::drawAxis(float axisSize) {
   // X
   glColor3f (1,0,0);
   glBegin(GL_LINES);
   glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
   glVertex3f(axisSize,0.0f, 0.0f); // ending point of the line
   glEnd( );
   
   // Y
   glColor3f (0,1,0);
   glBegin(GL_LINES);
   glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
   glVertex3f(0.0f, axisSize, 0.0f); // ending point of the line
   glEnd( );
   
   // Z
   glColor3f (0,0,1);
   glBegin(GL_LINES);
   glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
   glVertex3f(0.0f, 0.0f, axisSize); // ending point of the line
   glEnd( );
}

// Draw Triangle Pyramid with black edges
void ArUco::drawTrianglePyramid(GLdouble size) {

	GLfloat vertices[4][3] =
	{
		{size/2, size / 2, -size/2},
		{size / 2, -size / 2, -size/2},
		{-size / 2, size / 2, -size/2},
		{0, 0, size / 4}
	};

	GLint faces[4][3] =
	{
		{0, 3, 2},
		{1, 3, 0},
		{2, 3, 1},
		{2, 1, 0}
	};

	// Setting line width
	glLineWidth(2.0f);

	for (int i = 0; i < 4; i++) {
		glBegin(GL_TRIANGLES);
		glColor3f(0.6, 0.6, 0.1);
		glVertex3fv(&vertices[faces[i][0]][0]);
		glVertex3fv(&vertices[faces[i][1]][0]);
		glVertex3fv(&vertices[faces[i][2]][0]);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3fv(&vertices[faces[i][0]][0]);
		glVertex3fv(&vertices[faces[i][1]][0]);
		glVertex3fv(&vertices[faces[i][2]][0]);
		glEnd();
	}

}

// Draw Square Pyramid with black edges
void ArUco::drawSquarePyramid(GLdouble size) {

	GLfloat vertices[5][3] =
	{
		{size / 2, size / 2, -size / 2},
		{size / 2, -size / 2, -size / 2},
		{-size / 2, -size / 2, -size / 2},
		{-size / 2, size / 2, -size / 2},
		{0, 0, size / 4}
	};

	GLint Trianglefaces[4][3] =
	{
		{1, 0, 4},
		{2, 1, 4},
		{3, 2, 4},
		{0, 3, 4}
	};

	// Setting line width
	glLineWidth(2.0f);


	// drawing triangle faces
	for (int i = 0; i < 4; i++) {
		glBegin(GL_TRIANGLES);
		glColor3f(0.6, 0.6, 0.1);
		glVertex3fv(&vertices[Trianglefaces[i][0]][0]);
		glVertex3fv(&vertices[Trianglefaces[i][1]][0]);
		glVertex3fv(&vertices[Trianglefaces[i][2]][0]);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3fv(&vertices[Trianglefaces[i][0]][0]);
		glVertex3fv(&vertices[Trianglefaces[i][1]][0]);
		glVertex3fv(&vertices[Trianglefaces[i][2]][0]);
		glEnd();                                                                                                                                      
	}

}

// Stockage des coordonées et rayons des marqueurs
cv::Point2f marqueurPos[2] = {};
float marqueurRad[2] = {};

// GLUT functionnalities

// Drawing function
void ArUco::drawScene() {
   // If we do not have an image we don't do anyhting
   if (m_ResizedImage.rows==0)
      return;
   
   // On "reset" les matrices OpenGL de ModelView et de Projection
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // On deinit une vue orthographique de la taille de l'image OpenGL
   glOrtho(0, m_GlWindowSize.width, 0, m_GlWindowSize.height, -1.0, 1.0);
   // on definit le viewport correspond a un rendu "plein ecran"
   glViewport(0, 0, m_GlWindowSize.width , m_GlWindowSize.height);

   // on desactive les textures
   glDisable(GL_TEXTURE_2D);

   // On "flippe" l'axe des Y car OpenCV et OpenGL on un axe Y inverse pour les images/textures
   glPixelZoom( 1, -1);

   // On definit la position ou l'on va ecrire dans l'image
   glRasterPos3f(0, m_GlWindowSize.height, -1.0f);
   
   // On "dessine" les pixels contenus dans l'image OpenCV m_ResizedImage (donc l'image de la Webcam qui nous sert de fond)
   glDrawPixels (m_GlWindowSize.width, m_GlWindowSize.height, GL_RGB, GL_UNSIGNED_BYTE, m_ResizedImage.ptr(0));
   
   // On active ensuite le depth test pour les objets 3D
   glEnable(GL_DEPTH_TEST);
   
   // On passe en mode projection pour definir la bonne projection calculee par ArUco
   glMatrixMode(GL_PROJECTION);
   double proj_matrix[16];
   m_CameraParams.glGetProjectionMatrix(m_ResizedImage.size(),m_GlWindowSize,proj_matrix,0.01,100);
   glLoadIdentity();
   // on charge la matrice d'ArUco 
   glLoadMatrixd(proj_matrix);
   
   // On affiche le nombre de marqueurs (ne sert a rien)
   double modelview_matrix[16];
   std::cout << "Number of markers: " << m_Markers.size() << std::endl;
   
   // On nettoie le depth test pour qu'il ne considère que les pyramides
   glClear(GL_DEPTH_BUFFER_BIT);

   // Pour chaque marqueur detecte
   for (unsigned int m=0;m<m_Markers.size();m++)
   {
	   if (m_Markers[m].id == 144 || m_Markers[m].id == 217) {

		   // On recupere la matrice de modelview qui correspond au marqueur [m]
		   m_Markers[m].glGetModelViewMatrix(modelview_matrix);
		   glMatrixMode(GL_MODELVIEW);
		   glLoadIdentity();

		   // On stocke les coordonées et le rayon du marqueur
		   if (m_Markers[m].id == 144) {
			   marqueurPos[0] = m_Markers[m].getCenter();
			   marqueurRad[0] = m_Markers[m].getRadius();
		   }
		   else {
			   marqueurPos[1] = m_Markers[m].getCenter();
			   marqueurRad[1] = m_Markers[m].getRadius();
		   }


		   // on charge cette matrice pour se placer dans le repere de ce marqueur [m] 
		   glLoadMatrixd(modelview_matrix);

		   // On dessine les axes X Y Z
		   drawAxis(m_MarkerSize);

		   // On se deplace sur Z de la moitie du marqueur pour dessiner "sur" le plan du marqueur
		   glTranslatef(0, 0, m_MarkerSize / 2.);

		   // On sauvegarde la matrice courante
		   glPushMatrix();
		   // on choisit une couleur
		   glColor3f(1, 0.4f, 0.4f);

		   // Ajouter votre code ici !!

		   // Calcul de la distance entre 2 points
		   Point2f diff = marqueurPos[0] - marqueurPos[1];
		   float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
		   cout << "distance: " << dist << "seuil: " << marqueurRad[0] + marqueurRad[1] << endl;

		   // Si les marqueurs sont éloignés, on dessine une demi-pyramide sur chaque
		   if (dist > 1.2*(marqueurRad[0] + marqueurRad[1])) {
			   drawTrianglePyramid(m_MarkerSize);
		   }
		   // Si ils sont proche, on dessine pyramide entière sur un seul marqueur
		   else if (m_Markers[m].id == 217) {
			   drawSquarePyramid(m_MarkerSize);
		   }

		   // On re=charge la matrice que l'on a sauvegarde
		   glPopMatrix();
	   }
   }
   
   // Desactivation du depth test
   glDisable(GL_DEPTH_TEST);
}

// Idle function
void ArUco::idle(Mat newImage) {
   // Getting new image
   m_InputImage = newImage.clone();
  
   // Undistort image based on distorsion parameters
   m_UndInputImage.create(m_InputImage.size(),CV_8UC3);
   
   //transform color that by default is BGR to RGB because windows systems do not allow reading BGR images with opengl properly
   cv::cvtColor(m_InputImage,m_InputImage,cv::COLOR_BGR2RGB);
   
   //remove distorion in image ==> does not work very well (the YML file is not that of my camera)
   //cv::undistort(m_InputImage,m_UndInputImage, m_CameraParams.CameraMatrix, m_CameraParams.Distorsion);
   m_UndInputImage = m_InputImage.clone();
   
   //resize the image to the size of the GL window
   cv::resize(m_UndInputImage,m_ResizedImage,m_GlWindowSize);

   //detect markers
   m_PPDetector.detect(m_ResizedImage, m_Markers, m_CameraParams, m_MarkerSize, false);

}

// Resize function
void ArUco::resize(GLsizei iWidth, GLsizei iHeight) {
   m_GlWindowSize=Size(iWidth,iHeight);
   
   //not all sizes are allowed. OpenCv images have padding at the end of each line in these that are not aligned to 4 bytes
   if (iWidth*3%4!=0) {
      iWidth+=iWidth*3%4;//resize to avoid padding
      resize(iWidth, m_GlWindowSize.height);
   }
   else {
      //resize the image to the size of the GL window
      if (m_UndInputImage.rows!=0)
         cv::resize(m_UndInputImage, m_ResizedImage, m_GlWindowSize);
   }

}

// Test using ArUco to display a 3D cube in OpenCV
void ArUco::draw3DCube(cv::Mat img, int markerInd) {
   if(m_Markers.size() > markerInd) {
      aruco::CvDrawingUtils::draw3dCube(img, m_Markers[markerInd], m_CameraParams); 
   }
}

void ArUco::draw3DAxis(cv::Mat img, int markerInd) {
   if(m_Markers.size() > markerInd) {
      aruco::CvDrawingUtils::draw3dAxis(img, m_Markers[markerInd], m_CameraParams); 
   }
   
}
