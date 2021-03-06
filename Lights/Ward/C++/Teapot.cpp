#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <math.h>

#include <utils.h>
#include <MeshModuleLoading.h>
#include <MeshModuleDrawing.h>

#include <Teapot.h>


/**
 * Constructeur
 * @param material : matériau à appliquer
 */
Teapot::Teapot(WardMaterial* material)
{
    // charger le maillage
    m_Mesh = new Mesh("Teapot");
    MeshModuleLoading loader(m_Mesh);
    loader.loadObjFile("data/models/Teapot/teapot.obj", "", 0.02);

    // calculer les normales
    m_Mesh->computeNormals();

    // calculer les tangentes
    m_Mesh->computeTangents();

    // créer le VBOset
    MeshModuleDrawing renderer(m_Mesh);
    m_VBOset = renderer.createStripVBOset(material, true);
}


/**
 * dessine l'objet sur l'écran
 * @param mat4Projection : matrice de projection
 * @param mat4ModelView : matrice de vue
 */
void Teapot::onDraw(mat4& mat4Projection, mat4& mat4ModelView)
{
    // construire la matrice MV finale
    mat4 mat4ModelViewTeapot = mat4::clone(mat4ModelView);

    // décaler la théière vers le bas
    mat4::translate(mat4ModelViewTeapot, mat4ModelViewTeapot, vec3::fromValues(0.0,-0.7,0.0));

    // dessiner l'objet
    m_VBOset->onDraw(mat4Projection, mat4ModelViewTeapot);
}


/**
 * Cette méthode supprime les ressources allouées
 */
Teapot::~Teapot()
{
    delete m_Mesh;
    delete m_VBOset;
}
