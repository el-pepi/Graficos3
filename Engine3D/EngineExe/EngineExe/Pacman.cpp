#include "Pacman.h"
#include "Camera.h"
#include <iostream>
#include <time.h>
//---------------------------------------------------------------------------
float speedCamera = 0.5f;
float zoomCamera = 0.5f;
float rotationCamera = 0.5f;
//------------------------
void cameraControll(Input& input, Timer& timer, Camera* cam) {
	// Camera move
	if (input.keyDown(input.KEY_W)){
		cam->walk(zoomCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_S)){
		cam->walk(-zoomCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_Q)){
		cam->roll(rotationCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_E)){
		cam->roll(-rotationCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_D)){
		cam->strafe(speedCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_A)){
		cam->strafe(-speedCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_SPACE)){
		cam->fly(speedCamera * timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_LSHIFT)){
		cam->fly(-speedCamera * timer.timeBetweenFrames());
	}
	cam->yaw((float)input.mouseRelPosX() * 0.05f);
	cam->pitch((float)input.mouseRelPosY() * 0.05f);
}
//------------------------
float cubeRot = 0;
float cubeScale = 3;
//---------------------------------------------------------------------------
bool Pacman::init(Renderer& rendi){

	// camera config
	cam = new Camera(rendi);
	cam->setRender(rendi);
	cam->update();
	///////////////////////////////	

	nodo1 = new Node();
	nodo1->setName("Root");
	importador = new Importador(rendi);
	importador->importScene("fbxScene.dae", *nodo1,rendi);
	nodo1->setScale(1, 1, 1);
	//nodo1->setRotation(0, 0, 0, 0);
	nodo1->setPos(0, 0, 0);

	teapot = new Mesh(rendi);
	nodo1->getChild("Movil", *teapot);


	frustum = new Frustum(rendi);
	cam->setFrustum(frustum);

	_text.createText(0, -20, 1000, 1000, 20, "Arial","asdasdasd", rendi);
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){

	float RotModif = 0.01f * timer.timeBetweenFrames();
	float ScaleModif = 0.1f * timer.timeBetweenFrames();
	float PosModif = 1.0f * timer.timeBetweenFrames();

	_text.setText("");

	// Modificar traslacion Teapot
	if (input.keyDown(input.KEY_LEFT)) teapot->setPos(teapot->posX() + ScaleModif, teapot->posY(), teapot->posZ());
	if (input.keyDown(input.KEY_RIGHT))teapot->setPos(teapot->posX() - ScaleModif, teapot->posY(), teapot->posZ());
	if (input.keyDown(input.KEY_DOWN)) teapot->setPos(teapot->posX(), teapot->posY(), teapot->posZ() + ScaleModif);
	if (input.keyDown(input.KEY_UP))teapot->setPos(teapot->posX(), teapot->posY(), teapot->posZ() - ScaleModif);
	// Modificar escala Teapot
	//if (input.keyDown(input.KEY_UP))   teapot->setScale(teapot->scaleX(), teapot->scaleY() + RotModif, teapot->scaleZ());
	//if (input.keyDown(input.KEY_DOWN)) teapot->setScale(teapot->scaleX(), teapot->scaleY() - RotModif, teapot->scaleZ());
	// Modificar escala nodo1: K y L
	if (input.keyDown(input.KEY_K)) nodo1->setScale(nodo1->scaleX() + ScaleModif, nodo1->scaleY() + ScaleModif, nodo1->scaleZ() + ScaleModif);
	if (input.keyDown(input.KEY_L)) nodo1->setScale(nodo1->scaleX() - ScaleModif, nodo1->scaleY() - ScaleModif, nodo1->scaleZ() - ScaleModif);
	// Modificar traslacion nodo1: YGHJ
	if (input.keyDown(input.KEY_Y)) nodo1->setPos(nodo1->posX(),			nodo1->posY() + PosModif, nodo1->posZ());
	if (input.keyDown(input.KEY_H)) nodo1->setPos(nodo1->posX(),			nodo1->posY() - PosModif, nodo1->posZ());
	if (input.keyDown(input.KEY_G)) nodo1->setPos(nodo1->posX() - PosModif, nodo1->posY(),			  nodo1->posZ());
	if (input.keyDown(input.KEY_J)) nodo1->setPos(nodo1->posX() + PosModif, nodo1->posY(),			  nodo1->posZ());	



	//nodo1->setRotation(nodo1->rotationX() + 0.001, nodo1->rotationY(), nodo1->rotationZ());


	cameraControll(input, timer, cam);
	cam->update();
	cam->updateFrustum();

	nodo1->updateBV();
	nodo1->draw(renderer, cam->frustum->CheckCollision(nodo1->BV), *frustum , _text);

	 _text.setText(_text._text + "\n\n Drawn polygons: " + std::to_string(renderer.getDrawnFaces()) + "\n Total polygons: " + std::to_string(renderer.getTotalFaces()));
	 renderer.setDrawnFaces(0);
	 _text.draw(renderer);
	 renderer.SetCamPos(cam->posX, cam->posY, cam->posZ);
}
//---------------------------------------------------------------------------
