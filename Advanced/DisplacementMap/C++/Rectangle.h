#ifndef RECTANGLE_H
#define RECTANGLE_H

// Définition de la classe Rectangle

#include <vector>
#include <map>
#include <list>

#include <gl-matrix.h>
#include <Mesh.h>
#include <VBOset.h>

#include "DisplacementMaterial.h"


/**
 * Classe Rectangle.
 */
class Rectangle
{
public:

    /**
     * constructeur
     */
    Rectangle();

    /** destructeur, libère le VBOset et le maillage */
    ~Rectangle();

    /**
     * dessine l'objet sur l'écran
     * @param mat4Projection : matrice de projection
     * @param mat4ModelView : matrice de vue
     */
    void onDraw(mat4& mat4Projection, mat4& mat4ModelView);


private:

    // maillage
    Mesh* m_Mesh;

    // matériau
    DisplacementMaterial* m_Material;

    // VBOset
    VBOset* m_VBOset;

};

#endif
