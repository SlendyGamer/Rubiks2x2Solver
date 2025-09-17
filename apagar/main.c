#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "pilhas.h"
#include "actions.h"
#include <stdlib.h>
#include <string.h>

void drawCubeNoRotation(void);
// Estrutura para representar o estado do cubo
//typedef struct {
//    int pattern[24]; // Array de 0 a 23 mapeando quads para cores
//} No; // Não utilizada diretamente

float colors[24][3] = {
    {1.0f, 0.0f, 0.0f},  // 0: red
    {1.0f, 1.0f, 1.0f},  // 1: white
    {0.0f, 0.0f, 1.0f},  // 2: blue
    {0.0f, 0.0f, 1.0f},  // 3: blue
    {1.0f, 1.0f, 1.0f},  // 4: white
    {1.0f, 0.5f, 0.0f},  // 5: orange
    {1.0f, 1.0f, 0.0f},  // 6: yellow
    {0.0f, 0.0f, 1.0f},  // 7: blue
    {1.0f, 0.5f, 0.0f},  // 8: orange
    {1.0f, 1.0f, 0.0f},  // 9: yellow
    {1.0f, 0.0f, 0.0f},  // 10: red
    {0.0f, 0.0f, 1.0f},  // 11: blue
    {1.0f, 1.0f, 0.0f},  // 12: yellow
    {0.0f, 1.0f, 0.0f},  // 13: green
    {1.0f, 0.0f, 0.0f},  // 14: red
    {1.0f, 0.0f, 0.0f},  // 15: red
    {0.0f, 1.0f, 0.0f},  // 16: green
    {1.0f, 1.0f, 1.0f},  // 17: white
    {1.0f, 1.0f, 1.0f},  // 18: white
    {0.0f, 1.0f, 0.0f},  // 19: green
    {1.0f, 0.5f, 0.0f},  // 20: orange
    {1.0f, 1.0f, 0.0f},  // 21: yellow
    {1.0f, 0.5f, 0.0f},  // 22: orange
    {0.0f, 1.0f, 0.0f}   // 23: green
};

// Array global que mapeia cada quad a um índice de cor
int quadValues[24] = {
    18, 17, 4, 1,        // Front face (4 quads)
    12, 21, 9, 6,        // Back face
    22, 20, 8, 5,        // Left face
    15, 14, 0, 10,       // Right face
    3, 2, 7, 11,         // Top face
    23, 13, 19, 16       // Bottom face
};

int solution[24] = {
    18, 17, 4, 1,        // Front face (4 quads)
    12, 21, 9, 6,        // Back face
    22, 20, 8, 5,        // Left face
    15, 14, 0, 10,       // Right face
    3, 2, 7, 11,         // Top face
    23, 13, 19, 16       // Bottom face
};

float angleX = 30.0f;
float angleY = 0.0f;
float rotationAngle = 0.0f; // Ângulo da animação
char currentAxis = 0;       // Eixo atual ('x', 'y', 'z')

void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void drawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, int value) {
    glColor3fv(colors[value]);
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glEnd();
}

void drawCube(void) {
    int quadIndex = 0;
    float delta = 0.01f;

    // Salvar a matriz atual
    glPushMatrix();

    // Aplicar rotação da camada se houver animação
    if (rotationAngle > 0.0f && currentAxis != 0) {
        if (currentAxis == 'x'|| currentAxis == 'X') {
            glPushMatrix();
            if (currentAxis == 'x')
                glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
            else
                glRotatef(rotationAngle, -1.0f, 0.0f, 0.0f);
            // Right face (x = 1.0f, quads 12, 13, 14, 15)
            drawQuad(1.0f, -delta, delta,    1.0f, -delta, 1.0f,    1.0f, -1.0f, 1.0f,    1.0f, -1.0f, delta, quadValues[12]); // Bottom-left
            drawQuad(1.0f, -delta, -delta,    1.0f, -1.0f, -delta,    1.0f, -1.0f, -1.0f,    1.0f, -delta, -1.0f, quadValues[13]); // Bottom-right
            drawQuad(1.0f, delta, delta,    1.0f, 1.0f, delta,    1.0f, 1.0f, 1.0f,    1.0f, delta, 1.0f, quadValues[14]); // Top-left
            drawQuad(1.0f, delta, -delta,    1.0f, delta, -1.0f,    1.0f, 1.0f, -1.0f,    1.0f, 1.0f, -delta, quadValues[15]); // Top-right
            // Quads adjacentes afetados por rotate_x: frente (0, 1, 2, 3), esquerda (8, 9, 10, 11), topo (16, 17, 18, 19)
            drawQuad(1.0f, -1.0f, -1.0f,      delta, -1.0f, -1.0f,    delta, -delta, -1.0f,    1.0f, -delta, -1.0f, quadValues[4]); // Trás Bottom-left
            drawQuad(delta, -1.0f, 1.0f,    1.0f, -1.0f, 1.0f,      1.0f, -delta, 1.0f,      delta, -delta, 1.0f, quadValues[1]); // Frente Bottom-right
            drawQuad(1.0f, delta, -1.0f,      delta, delta, -1.0f,    delta, 1.0f, -1.0f,      1.0f, 1.0f, -1.0f, quadValues[6]); // Trás Top-left
            drawQuad(delta, delta, 1.0f,    1.0f, delta, 1.0f,      1.0f, 1.0f, 1.0f,        delta, 1.0f, 1.0f, quadValues[3]); // Frente Top-right
            drawQuad(delta, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -delta,    delta, -1.0f, -delta, quadValues[21]); // Base Bottom-right
            drawQuad(delta, -1.0f, delta,    1.0f, -1.0f, delta,    1.0f, -1.0f, 1.0f,    delta, -1.0f, 1.0f, quadValues[23]); // Base Top-right
            drawQuad(delta, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, delta,    delta, 1.0f, delta, quadValues[17]); // Topo Bottom-right
            drawQuad(delta, 1.0f, -delta,    1.0f, 1.0f, -delta,    1.0f, 1.0f, -1.0f,    delta, 1.0f, -1.0f, quadValues[19]); // Topo Top-right
            glPopMatrix();
            // Faces não rotacionantes
            drawQuad(-1.0f, -1.0f, 1.0f,    -delta, -1.0f, 1.0f,    -delta, -delta, 1.0f,    -1.0f, -delta, 1.0f, quadValues[0]); // Frente Bottom-left
            drawQuad(-1.0f, delta, 1.0f,    -delta, delta, 1.0f,    -delta, 1.0f, 1.0f,      -1.0f, 1.0f, 1.0f, quadValues[2]); // Frente Top-left
            drawQuad(-1.0f, -1.0f, -delta,  -1.0f, -delta, -delta,  -1.0f, -delta, -1.0f,    -1.0f, -1.0f, -1.0f, quadValues[8]); // Esquerda Bottom-left
            drawQuad(-1.0f, -1.0f, 1.0f,    -1.0f, -delta, 1.0f,    -1.0f, -delta, delta,    -1.0f, -1.0f, delta, quadValues[9]); // Esquerda Bottom-right
            drawQuad(-1.0f, delta, -delta,     -1.0f, 1.0f, -delta,      -1.0f, 1.0f, -1.0f,    -1.0f, delta, -1.0f, quadValues[10]); // Esquerda Top-left
            drawQuad(-1.0f, delta, 1.0f,     -1.0f, 1.0f, 1.0f,      -1.0f, 1.0f, delta,    -1.0f, delta, delta, quadValues[11]); // Esquerda Top-right
            drawQuad(-1.0f, 1.0f, 1.0f,    -delta, 1.0f, 1.0f,    -delta, 1.0f, delta,    -1.0f, 1.0f, delta, quadValues[16]); // Topo Bottom-left
            drawQuad(-1.0f, 1.0f, -delta,    -delta, 1.0f, -delta,    -delta, 1.0f, -1.0f,    -1.0f, 1.0f, -1.0f, quadValues[18]); // Topo Top-left
            drawQuad(-delta, -1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -delta, -1.0f,    -delta, -delta, -1.0f, quadValues[5]); // Trás Bottom-right
            drawQuad(-delta, delta, -1.0f,    -1.0f, delta, -1.0f,    -1.0f, 1.0f, -1.0f,      -delta, 1.0f, -1.0f, quadValues[7]); // Trás Top-right
            drawQuad(-1.0f, -1.0f, -1.0f,    -delta, -1.0f, -1.0f,    -delta, -1.0f, -delta,    -1.0f, -1.0f, -delta, quadValues[20]); // Base Bottom-left
            drawQuad(-1.0f, -1.0f, delta,    -delta, -1.0f, delta,    -delta, -1.0f, 1.0f,   -1.0f, -1.0f, 1.0f, quadValues[22]); // Base Top-left
        } else if (currentAxis == 'y'|| currentAxis == 'Y') {
            glPushMatrix();
            if (currentAxis == 'y')
                glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
            else
                glRotatef(rotationAngle, 0.0f, -1.0f, 0.0f);
            // Top face (y = 1.0f, quads 16, 17, 18, 19)
            drawQuad(-1.0f, 1.0f, 1.0f,    -delta, 1.0f, 1.0f,    -delta, 1.0f, delta,    -1.0f, 1.0f, delta, quadValues[16]); // Bottom-left
            drawQuad(delta, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, delta,    delta, 1.0f, delta, quadValues[17]); // Bottom-right
            drawQuad(-1.0f, 1.0f, -delta,    -delta, 1.0f, -delta,    -delta, 1.0f, -1.0f,    -1.0f, 1.0f, -1.0f, quadValues[18]); // Top-left
            drawQuad(delta, 1.0f, -delta,    1.0f, 1.0f, -delta,    1.0f, 1.0f, -1.0f,    delta, 1.0f, -1.0f, quadValues[19]); // Top-right
            // Quads adjacentes afetados por rotate_y: frente (2, 3), trás (6, 7), esquerda (10, 11), direita (14, 15)
            drawQuad(-1.0f, delta, 1.0f,    -delta, delta, 1.0f,    -delta, 1.0f, 1.0f,      -1.0f, 1.0f, 1.0f, quadValues[2]); // Frente Top-left
            drawQuad(delta, delta, 1.0f,    1.0f, delta, 1.0f,      1.0f, 1.0f, 1.0f,        delta, 1.0f, 1.0f, quadValues[3]); // Frente Top-right
            drawQuad(1.0f, delta, -1.0f,      delta, delta, -1.0f,    delta, 1.0f, -1.0f,      1.0f, 1.0f, -1.0f, quadValues[6]); // Trás Top-left
            drawQuad(-delta, delta, -1.0f,    -1.0f, delta, -1.0f,    -1.0f, 1.0f, -1.0f,      -delta, 1.0f, -1.0f, quadValues[7]); // Trás Top-right
            drawQuad(-1.0f, delta, -delta,     -1.0f, 1.0f, -delta,      -1.0f, 1.0f, -1.0f,    -1.0f, delta, -1.0f, quadValues[10]); // Esquerda Top-left
            drawQuad(-1.0f, delta, 1.0f,     -1.0f, 1.0f, 1.0f,      -1.0f, 1.0f, delta,    -1.0f, delta, delta, quadValues[11]); // Esquerda Top-right
            drawQuad(1.0f, delta, delta,    1.0f, 1.0f, delta,    1.0f, 1.0f, 1.0f,    1.0f, delta, 1.0f, quadValues[14]); // Direita Top-left
            drawQuad(1.0f, delta, -delta,    1.0f, delta, -1.0f,    1.0f, 1.0f, -1.0f,    1.0f, 1.0f, -delta, quadValues[15]); // Direita Top-right
            glPopMatrix();
            // Faces não rotacionantes
            drawQuad(-1.0f, -1.0f, 1.0f,    -delta, -1.0f, 1.0f,    -delta, -delta, 1.0f,    -1.0f, -delta, 1.0f, quadValues[0]); // Frente Bottom-left
            drawQuad(delta, -1.0f, 1.0f,    1.0f, -1.0f, 1.0f,      1.0f, -delta, 1.0f,      delta, -delta, 1.0f, quadValues[1]); // Frente Bottom-right
            drawQuad(1.0f, -1.0f, -1.0f,      delta, -1.0f, -1.0f,    delta, -delta, -1.0f,    1.0f, -delta, -1.0f, quadValues[4]); // Trás Bottom-left
            drawQuad(-delta, -1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -delta, -1.0f,    -delta, -delta, -1.0f, quadValues[5]); // Trás Bottom-right
            drawQuad(-1.0f, -1.0f, -delta,  -1.0f, -delta, -delta,  -1.0f, -delta, -1.0f,    -1.0f, -1.0f, -1.0f, quadValues[8]); // Esquerda Bottom-left
            drawQuad(-1.0f, -1.0f, 1.0f,    -1.0f, -delta, 1.0f,    -1.0f, -delta, delta,    -1.0f, -1.0f, delta, quadValues[9]); // Esquerda Bottom-right
            drawQuad(1.0f, -delta, delta,    1.0f, -delta, 1.0f,    1.0f, -1.0f, 1.0f,    1.0f, -1.0f, delta, quadValues[12]); // Direita Bottom-left
            drawQuad(1.0f, -delta, -delta,    1.0f, -1.0f, -delta,    1.0f, -1.0f, -1.0f,    1.0f, -delta, -1.0f, quadValues[13]); // Direita Bottom-right
            drawQuad(-1.0f, -1.0f, -1.0f,    -delta, -1.0f, -1.0f,    -delta, -1.0f, -delta,    -1.0f, -1.0f, -delta, quadValues[20]); // Base Bottom-left
            drawQuad(delta, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -delta,    delta, -1.0f, -delta, quadValues[21]); // Base Bottom-right
            drawQuad(-1.0f, -1.0f, delta,    -delta, -1.0f, delta,    -delta, -1.0f, 1.0f,   -1.0f, -1.0f, 1.0f, quadValues[22]); // Base Top-left
            drawQuad(delta, -1.0f, delta,    1.0f, -1.0f, delta,    1.0f, -1.0f, 1.0f,    delta, -1.0f, 1.0f, quadValues[23]); // Base Top-right
        } else if (currentAxis == 'z'|| currentAxis == 'Z') {
            glPushMatrix();
            if (currentAxis == 'z')
                glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
            else
                glRotatef(rotationAngle, 0.0f, 0.0f, -1.0f);
            // Front face (z = 1.0f, quads 0, 1, 2, 3)
            drawQuad(-1.0f, -1.0f, 1.0f,    -delta, -1.0f, 1.0f,    -delta, -delta, 1.0f,    -1.0f, -delta, 1.0f, quadValues[0]); // Bottom-left
            drawQuad(delta, -1.0f, 1.0f,    1.0f, -1.0f, 1.0f,      1.0f, -delta, 1.0f,      delta, -delta, 1.0f, quadValues[1]); // Bottom-right
            drawQuad(-1.0f, delta, 1.0f,    -delta, delta, 1.0f,    -delta, 1.0f, 1.0f,      -1.0f, 1.0f, 1.0f, quadValues[2]); // Top-left
            drawQuad(delta, delta, 1.0f,    1.0f, delta, 1.0f,      1.0f, 1.0f, 1.0f,        delta, 1.0f, 1.0f, quadValues[3]); // Top-right
            // Quads adjacentes afetados por rotate_z: esquerda (9, 11), direita (12, 14), topo (16, 17), base (22, 23)
            drawQuad(-1.0f, -1.0f, 1.0f,    -1.0f, -delta, 1.0f,    -1.0f, -delta, delta,    -1.0f, -1.0f, delta, quadValues[9]); // Esquerda Bottom-right
            drawQuad(-1.0f, delta, 1.0f,     -1.0f, 1.0f, 1.0f,      -1.0f, 1.0f, delta,    -1.0f, delta, delta, quadValues[11]); // Esquerda Top-right
            drawQuad(1.0f, -delta, delta,    1.0f, -delta, 1.0f,    1.0f, -1.0f, 1.0f,    1.0f, -1.0f, delta, quadValues[12]); // Direita Bottom-left
            drawQuad(1.0f, delta, delta,    1.0f, 1.0f, delta,    1.0f, 1.0f, 1.0f,    1.0f, delta, 1.0f, quadValues[14]); // Direita Top-left
            drawQuad(-1.0f, 1.0f, 1.0f,    -delta, 1.0f, 1.0f,    -delta, 1.0f, delta,    -1.0f, 1.0f, delta, quadValues[16]); // Topo Bottom-left
            drawQuad(delta, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, delta,    delta, 1.0f, delta, quadValues[17]); // Topo Bottom-right
            drawQuad(-1.0f, -1.0f, delta,    -delta, -1.0f, delta,    -delta, -1.0f, 1.0f,   -1.0f, -1.0f, 1.0f, quadValues[22]); // Base Top-left
            drawQuad(delta, -1.0f, delta,    1.0f, -1.0f, delta,    1.0f, -1.0f, 1.0f,    delta, -1.0f, 1.0f, quadValues[23]); // Base Top-right
            glPopMatrix();
            // Faces não rotacionantes
            drawQuad(1.0f, -1.0f, -1.0f,      delta, -1.0f, -1.0f,    delta, -delta, -1.0f,    1.0f, -delta, -1.0f, quadValues[4]); // Trás Bottom-left
            drawQuad(-delta, -1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -delta, -1.0f,    -delta, -delta, -1.0f, quadValues[5]); // Trás Bottom-right
            drawQuad(1.0f, delta, -1.0f,      delta, delta, -1.0f,    delta, 1.0f, -1.0f,      1.0f, 1.0f, -1.0f, quadValues[6]); // Trás Top-left
            drawQuad(-delta, delta, -1.0f,    -1.0f, delta, -1.0f,    -1.0f, 1.0f, -1.0f,      -delta, 1.0f, -1.0f, quadValues[7]); // Trás Top-right
            drawQuad(-1.0f, -1.0f, -delta,  -1.0f, -delta, -delta,  -1.0f, -delta, -1.0f,    -1.0f, -1.0f, -1.0f, quadValues[8]); // Esquerda Bottom-left
            drawQuad(-1.0f, delta, -delta,     -1.0f, 1.0f, -delta,      -1.0f, 1.0f, -1.0f,    -1.0f, delta, -1.0f, quadValues[10]); // Esquerda Top-left
            drawQuad(1.0f, -delta, -delta,    1.0f, -1.0f, -delta,    1.0f, -1.0f, -1.0f,    1.0f, -delta, -1.0f, quadValues[13]); // Direita Bottom-right
            drawQuad(1.0f, delta, -delta,    1.0f, delta, -1.0f,    1.0f, 1.0f, -1.0f,    1.0f, 1.0f, -delta, quadValues[15]); // Direita Top-right
            drawQuad(-1.0f, 1.0f, -delta,    -delta, 1.0f, -delta,    -delta, 1.0f, -1.0f,    -1.0f, 1.0f, -1.0f, quadValues[18]); // Topo Top-left
            drawQuad(delta, 1.0f, -delta,    1.0f, 1.0f, -delta,    1.0f, 1.0f, -1.0f,    delta, 1.0f, -1.0f, quadValues[19]); // Topo Top-right
            drawQuad(-1.0f, -1.0f, -1.0f,    -delta, -1.0f, -1.0f,    -delta, -1.0f, -delta,    -1.0f, -1.0f, -delta, quadValues[20]); // Base Bottom-left
            drawQuad(delta, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -delta,    delta, -1.0f, -delta, quadValues[21]); // Base Bottom-right
        } else {
            // Sem rotação, desenha o cubo inteiro normalmente
            drawCubeNoRotation();
        }
    } else {
        // Desenha o cubo sem rotação
        drawCubeNoRotation();
    }

    glPopMatrix();
}

// Função auxiliar para desenhar o cubo sem rotação
void drawCubeNoRotation(void) {
    int quadIndex = 0;
    float delta = 0.01f;

    // Front face (z = 1.0f)
    drawQuad(-1.0f, -1.0f, 1.0f,    -delta, -1.0f, 1.0f,    -delta, -delta, 1.0f,    -1.0f, -delta, 1.0f, quadValues[quadIndex++]); // Bottom-left
    drawQuad(delta, -1.0f, 1.0f,    1.0f, -1.0f, 1.0f,      1.0f, -delta, 1.0f,      delta, -delta, 1.0f, quadValues[quadIndex++]); // Bottom-right
    drawQuad(-1.0f, delta, 1.0f,    -delta, delta, 1.0f,    -delta, 1.0f, 1.0f,      -1.0f, 1.0f, 1.0f, quadValues[quadIndex++]); // Top-left
    drawQuad(delta, delta, 1.0f,    1.0f, delta, 1.0f,      1.0f, 1.0f, 1.0f,        delta, 1.0f, 1.0f, quadValues[quadIndex++]); // Top-right

    // Back face (z = -1.0f)
    drawQuad(1.0f, -1.0f, -1.0f,      delta, -1.0f, -1.0f,    delta, -delta, -1.0f,    1.0f, -delta, -1.0f, quadValues[quadIndex++]); // Bottom-left
    drawQuad(-delta, -1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f, -delta, -1.0f,    -delta, -delta, -1.0f, quadValues[quadIndex++]); // Bottom-right
    drawQuad(1.0f, delta, -1.0f,      delta, delta, -1.0f,    delta, 1.0f, -1.0f,      1.0f, 1.0f, -1.0f, quadValues[quadIndex++]); // Top-left
    drawQuad(-delta, delta, -1.0f,    -1.0f, delta, -1.0f,    -1.0f, 1.0f, -1.0f,      -delta, 1.0f, -1.0f, quadValues[quadIndex++]); // Top-right

    // Left face (x = -1.0f)
    drawQuad(-1.0f, -1.0f, -delta,  -1.0f, -delta, -delta,  -1.0f, -delta, -1.0f,    -1.0f, -1.0f, -1.0f, quadValues[quadIndex++]); // Bottom-left
    drawQuad(-1.0f, -1.0f, 1.0f,    -1.0f, -delta, 1.0f,    -1.0f, -delta, delta,    -1.0f, -1.0f, delta, quadValues[quadIndex++]); // Bottom-right
    drawQuad(-1.0f, delta, -delta,     -1.0f, 1.0f, -delta,      -1.0f, 1.0f, -1.0f,    -1.0f, delta, -1.0f, quadValues[quadIndex++]); // Top-left
    drawQuad(-1.0f, delta, 1.0f,     -1.0f, 1.0f, 1.0f,      -1.0f, 1.0f, delta,    -1.0f, delta, delta, quadValues[quadIndex++]); // Top-right

    // Right face (x = 1.0f, viewed from x positive, ccw)
    drawQuad(1.0f, -delta, delta,    1.0f, -delta, 1.0f,    1.0f, -1.0f, 1.0f,    1.0f, -1.0f, delta, quadValues[quadIndex++]); // Bottom-left
    drawQuad(1.0f, -delta, -delta,    1.0f, -1.0f, -delta,    1.0f, -1.0f, -1.0f,    1.0f, -delta, -1.0f, quadValues[quadIndex++]); // Bottom-right
    drawQuad(1.0f, delta, delta,    1.0f, 1.0f, delta,    1.0f, 1.0f, 1.0f,    1.0f, delta, 1.0f, quadValues[quadIndex++]); // Top-left
    drawQuad(1.0f, delta, -delta,    1.0f, delta, -1.0f,    1.0f, 1.0f, -1.0f,    1.0f, 1.0f, -delta, quadValues[quadIndex++]); // Top-right

    // Top face (y = 1.0f)
    drawQuad(-1.0f, 1.0f, 1.0f,    -delta, 1.0f, 1.0f,    -delta, 1.0f, delta,    -1.0f, 1.0f, delta, quadValues[quadIndex++]); // Bottom-left
    drawQuad(delta, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, delta,    delta, 1.0f, delta, quadValues[quadIndex++]); // Bottom-right
    drawQuad(-1.0f, 1.0f, -delta,    -delta, 1.0f, -delta,    -delta, 1.0f, -1.0f,    -1.0f, 1.0f, -1.0f, quadValues[quadIndex++]); // Top-left
    drawQuad(delta, 1.0f, -delta,    1.0f, 1.0f, -delta,    1.0f, 1.0f, -1.0f,    delta, 1.0f, -1.0f, quadValues[quadIndex++]); // Top-right

    // Bottom face (y = -1.0f, viewed from y negative, ccw)
    drawQuad(-1.0f, -1.0f, -1.0f,    -delta, -1.0f, -1.0f,    -delta, -1.0f, -delta,    -1.0f, -1.0f, -delta, quadValues[quadIndex++]); // Bottom-left
    drawQuad(delta, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -delta,    delta, -1.0f, -delta, quadValues[quadIndex++]); // Bottom-right
    drawQuad(-1.0f, -1.0f, delta,    -delta, -1.0f, delta,    -delta, -1.0f, 1.0f,   -1.0f, -1.0f, 1.0f, quadValues[quadIndex++]); // Top-left
    drawQuad(delta, -1.0f, delta,    1.0f, -1.0f, delta,    1.0f, -1.0f, 1.0f,    delta, -1.0f, 1.0f, quadValues[quadIndex++]); // Top-right
}

void drawAxes(void) {
    glLineWidth(2.0f); // Espessura das linhas dos eixos
    glBegin(GL_LINES);
    
    // Eixo X (vermelho, apenas direção positiva, face direita)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); // Centro
    glVertex3f(2.0f, 0.0f, 0.0f); // Fim (x=2.0, face direita)
    
    // Eixo Y (verde, apenas direção positiva, face topo)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); // Centro
    glVertex3f(0.0f, 2.0f, 0.0f); // Fim (y=2.0, face topo)
    
    // Eixo Z (azul, apenas direção positiva, face frente)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); // Centro
    glVertex3f(0.0f, 0.0f, 2.0f); // Fim (z=2.0, face frente)
    glEnd();

    // Desativar teste de profundidade para rótulos
    glDisable(GL_DEPTH_TEST);
    
    // Salvar matrizes atuais
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Obter matrizes para projeção 3D -> 2D
    GLdouble modelview[16], projection[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Coordenadas 3D das extremidades dos eixos
    GLdouble x_end[3] = {2.0, 0.0, 0.0};  // Fim do eixo x
    GLdouble y_end[3] = {0.0, 2.0, 0.0};  // Fim do eixo y
    GLdouble z_end[3] = {0.0, 0.0, 2.0};  // Fim do eixo z

    GLdouble winX, winY, winZ;

    // Rótulo "x" (vermelho)
    gluProject(x_end[0], x_end[1], x_end[2], modelview, projection, viewport, &winX, &winY, &winZ);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(winX + 10, winY + 5); // Ajuste para visibilidade
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'x');

    // Rótulo "y" (verde)
    gluProject(y_end[0], y_end[1], y_end[2], modelview, projection, viewport, &winX, &winY, &winZ);
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(winX + 25, winY + 5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'y');

    // Rótulo "z" (azul)
    gluProject(z_end[0], z_end[1], z_end[2], modelview, projection, viewport, &winX, &winY, &winZ);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(winX + 40, winY + 5);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'z');

    // Restaurar matrizes
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    // Reativar teste de profundidade
    glEnable(GL_DEPTH_TEST);
}

void rotate_x(void) {
    int aux;
    // Ciclo 1: 1 → 16 → 12 → 11 → 1
    aux = quadValues[3];
    quadValues[3] = quadValues[19];
    quadValues[19] = quadValues[4];
    quadValues[4] = quadValues[23];
    quadValues[23] = aux;

    // Ciclo 2: 17 → 13 → 9 → 2 → 17
    aux = quadValues[1];
    quadValues[1] = quadValues[17];
    quadValues[17] = quadValues[6];
    quadValues[6] = quadValues[21];
    quadValues[21] = aux;

    // Ciclo 3: 0 → 15 → 14 → 10 → 0
    aux = quadValues[14];
    quadValues[14] = quadValues[15];
    quadValues[15] = quadValues[13];
    quadValues[13] = quadValues[12];
    quadValues[12] = aux;
}

void rotate_NOTx(void) //ok
{
    int aux = quadValues[3];
    quadValues[3] = quadValues[23];
    quadValues[23] = quadValues[4];
    quadValues[4] = quadValues[19];
    quadValues[19] = aux;

    // Ciclo 2: 17 → 2 → 9 → 13 → 17
    aux = quadValues[1];
    quadValues[1] = quadValues[21];
    quadValues[21] = quadValues[6];
    quadValues[6] = quadValues[17];
    quadValues[17] = aux;

    // Ciclo 3: 0 → 10 → 14 → 15 → 0
    aux = quadValues[14];
    quadValues[14] = quadValues[12];
    quadValues[12] = quadValues[13];
    quadValues[13] = quadValues[15];
    quadValues[15] = aux;
}

void rotate_y(void) {
    int aux;
    // Ciclo 1: 0 → 9 → 8 → 4 → 0
    aux = quadValues[14];
    quadValues[14] = quadValues[2];
    quadValues[2] = quadValues[10];
    quadValues[10] = quadValues[6];
    quadValues[6] = aux;

    // Ciclo 2: 10 → 6 → 5 → 1 → 10
    aux = quadValues[15];
    quadValues[15] = quadValues[3];
    quadValues[3] = quadValues[11];
    quadValues[11] = quadValues[7];
    quadValues[7] = aux;

    // Ciclo 3: 2 → 11 → 7 → 3 → 2
    aux = quadValues[17];
    quadValues[17] = quadValues[16];
    quadValues[16] = quadValues[18];
    quadValues[18] = quadValues[19];
    quadValues[19] = aux;
}

void rotate_NOTy(void) //ok
{
    int aux;
    // Ciclo 1: 0 → 9 → 8 → 4 → 0
    aux = quadValues[14];
    quadValues[14] = quadValues[6];
    quadValues[6] = quadValues[10];
    quadValues[10] = quadValues[2];
    quadValues[2] = aux;

    // Ciclo 2: 10 → 6 → 5 → 1 → 10
    aux = quadValues[15];
    quadValues[15] = quadValues[7];
    quadValues[7] = quadValues[11];
    quadValues[11] = quadValues[3];
    quadValues[3] = aux;

    // Ciclo 3: 2 → 11 → 7 → 3 → 2
    aux = quadValues[17];
    quadValues[17] = quadValues[19];
    quadValues[19] = quadValues[18];
    quadValues[18] = quadValues[16];
    quadValues[16] = aux;
}

void rotate_z(void) {
    int aux;
    // Ciclo 1: 5 → 19 → 15 → 2 → 5
    aux = quadValues[11];
    quadValues[11] = quadValues[17];
    quadValues[17] = quadValues[12];
    quadValues[12] = quadValues[22];
    quadValues[22] = aux;

    // Ciclo 2: 20 → 16 → 0 → 3 → 20
    aux = quadValues[9];
    quadValues[9] = quadValues[16];
    quadValues[16] = quadValues[14];
    quadValues[14] = quadValues[23];
    quadValues[23] = aux;

    // Ciclo 3: 4 → 18 → 17 → 1 → 4
    aux = quadValues[2];
    quadValues[2] = quadValues[3];
    quadValues[3] = quadValues[1];
    quadValues[1] = quadValues[0];
    quadValues[0] = aux;
}

void rotate_NOTz(void)
{
    int aux;
    // Ciclo 1: 5 → 19 → 15 → 2 → 5
    aux = quadValues[11];
    quadValues[11] = quadValues[22];
    quadValues[22] = quadValues[12];
    quadValues[12] = quadValues[17];
    quadValues[17] = aux;

    // Ciclo 2: 20 → 16 → 0 → 3 → 20
    aux = quadValues[9];
    quadValues[9] = quadValues[23];
    quadValues[23] = quadValues[14];
    quadValues[14] = quadValues[16];
    quadValues[16] = aux;

    // Ciclo 3: 4 → 18 → 17 → 1 → 4
    aux = quadValues[2];
    quadValues[2] = quadValues[0];
    quadValues[0] = quadValues[1];
    quadValues[1] = quadValues[3];
    quadValues[3] = aux;
}

void animateRotation(int value) {
    rotationAngle += 5.0f; // Incrementa 5 graus por frame
    if (rotationAngle >= 90.0f) {
        // Final da animação, aplicar a rotação lógica
        if (currentAxis == 'x') rotate_x();
        else if (currentAxis == 'X') rotate_NOTx();
        else if (currentAxis == 'y') rotate_y();
        else if (currentAxis == 'Y') rotate_NOTy();
        else if (currentAxis == 'z') rotate_z();
        else if (currentAxis == 'Z') rotate_NOTz();
        rotationAngle = 0.0f; // Resetar animação
        currentAxis = 0;      // Resetar eixo
    } else {
        // Continuar animação
        glutTimerFunc(20, animateRotation, 0);
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (rotationAngle == 0.0f) { // Só permitir nova rotação se a anterior terminou
        if (key == 'x' ) {
            currentAxis = 'x';
            rotationAngle = 0.0f;
            glutTimerFunc(20, animateRotation, 0);
        } else if (key == 'X') {
            currentAxis = 'X';
            rotationAngle = 0.0f;
            glutTimerFunc(20, animateRotation, 0);
        } 
        
        else if (key == 'y') {
        currentAxis = 'y';
        rotationAngle = 0.0f;
            glutTimerFunc(20, animateRotation, 0);
        } else if (key == 'Y') {
            currentAxis = 'Y';
            rotationAngle = 0.0f;
            glutTimerFunc(20, animateRotation, 0);
        } 
        
        else if (key == 'z') {
        currentAxis = 'z';
        rotationAngle = 0.0f;
        glutTimerFunc(20, animateRotation, 0);
        } else if (key == 'Z') {
            currentAxis = 'Z';
            rotationAngle = 0.0f;
            glutTimerFunc(20, animateRotation, 0);
        }
        
        else if (key == 'd' || key == 'D') {
            No* state = (No*)malloc(sizeof(No));
            memcpy(state->pattern, quadValues, 24 * sizeof(int));
            Pilha* p = CriaPilha();
            if (dfs(p, state, solution))
            {
                printf("sucesso\n");
            }
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    drawCube();
    drawAxes();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        angleX -= 5.0f;
    } else if (key == GLUT_KEY_DOWN) {
        angleX += 5.0f;
    } else if (key == GLUT_KEY_RIGHT) {
        angleY += 5.0f;
    } else if (key == GLUT_KEY_LEFT) {
        angleY -= 5.0f;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cubo Simples com OpenGL");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}