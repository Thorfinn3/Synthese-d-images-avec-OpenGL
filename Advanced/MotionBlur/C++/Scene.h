#ifndef SCENE_H
#define SCENE_H

// Définition de la classe Scene

#include <gl-matrix.h>
#include <utils.h>
#include <TurnTableScene.h>
#include <MeshObject.h>
#include <SoftSpotLight.h>
#include <SkyBackground.h>
#include <FrameBufferObject.h>


class Scene: public TurnTableScene
{
private:

    // objets de la scène
    MeshObject* m_Lorry;
    MeshObject* m_PalmTree;
    MeshObject* m_Ground;

    SoftSpotLight* m_Light0;
    SoftSpotLight* m_Light1;
    SkyBackground* m_SkyBackground;

public:
    static const int IMAGES_COUNT = 12;
private:
    std::vector<FrameBufferObject*> m_FBOimages;
    int m_CurrentFBOnumber;

public:

    /** constructeur, crée les objets 3D à dessiner */
    Scene();

    /** destructeur, libère les ressources */
    ~Scene();

    /**
     * appelée quand la taille de la vue OpenGL change
     * @param width : largeur en nombre de pixels de la fenêtre
     * @param height : hauteur en nombre de pixels de la fenêtre
     */
    void onSurfaceChanged(int width, int height);

    /**
     * dessin des objets de la scène sur l'écran
     * @param mat4Projection : matrice de projection
     * @param mat4ModelView : matrice de vue
     */
    void onDraw(mat4& mat4Projection, mat4& mat4ModelView);

    /** Dessine l'image courante */
    void onDrawFrame();

};

#endif
