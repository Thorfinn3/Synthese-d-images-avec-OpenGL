#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <sstream>

#include <utils.h>
#include <AppleMaterial.h>


/**
 * Constructeur
 */
AppleMaterial::AppleMaterial() : Material("AppleMaterial")
{
    // compiler le shader
    compileShader();
}


/**
 * retourne le source du Vertex Shader
 */
std::string AppleMaterial::getVertexShader()
{
    const char* srcVertexShader =
        "#version 300 es\n"
        "in vec3 glVertex;\n"
        "in vec2 glTexCoord;\n"
        "out vec2 frgTexCoord;\n"
        "uniform mat4 mat4ModelView;\n"
        "uniform mat4 mat4Projection;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mat4Projection * mat4ModelView * vec4(glVertex, 1.0);\n"
        "    frgTexCoord = glTexCoord;\n"
        "}";
    return srcVertexShader;
}


/**
 * retourne le source du Fragment Shader
 */
std::string AppleMaterial::getFragmentShader()
{
    const char* srcFragmentShader =
        "#version 300 es\n"
        "precision mediump float;\n"
        "in vec2 frgTexCoord;\n"
        "out vec4 glFragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    // multiplier (s,t) afin de faire une répétition\n"
        "    vec2 texCoord = fract(frgTexCoord * vec2(16.0, 8.0));\n"
        "    // distance entre (s,t) et le centre (0.5, 0.5)\n"
        "    float dist = distance(texCoord, vec2(0.5,0.5));\n"
        "    // selon la distance : jaune ou rouge\n"
        "    if (dist > 0.4) {\n"
        "        glFragColor = vec4(1.0, 1.0, 0.1, 1.0);\n"
        "    } else {\n"
        "        glFragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "    }\n"
        "}";
    return srcFragmentShader;
}


/**
 * crée et retourne un VBOset pour ce matériau, afin qu'il soit rempli par un maillage
 * @return le VBOset du matériau
 */
VBOset* AppleMaterial::createVBOset()
{
    // créer le VBOset et spécifier les noms des attribute nécessaires à ce matériau
    VBOset* vboset = Material::createVBOset();
    vboset->addAttribute(MeshVertex::ID_ATTR_TEXCOORD, Utils::VEC2, "glTexCoord");
    return vboset;
}


/**
 * Cette méthode supprime les ressources allouées
 */
AppleMaterial::~AppleMaterial()
{
}
