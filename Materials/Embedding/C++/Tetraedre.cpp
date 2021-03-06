// Définition de la classe Tetraedre

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <math.h>

#include <utils.h>

#include <Tetraedre.h>



/**
 * Constructeur
 */
Tetraedre::Tetraedre() throw (std::string)
{
    /// Shader
    const char* srcVertexShader =
        "#version 300 es\n"
        "uniform mat4 mat4Projection;\n"
        "uniform mat4 mat4ModelView;\n"
        "in vec3 glVertex;\n"
        "in vec3 glColor;\n"
        "out vec3 frgColor;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mat4Projection * mat4ModelView * vec4(glVertex, 1.0);\n"
        "    frgColor = glColor;\n"
        "}";

    const char* srcFragmentShader =
        "#version 300 es\n"
        "precision mediump float;\n"
        "in vec3 frgColor;\n"
        "out vec4 glFragColor;\n"
        "void main()\n"
        "{\n"
        "  glFragColor = vec4(frgColor, 1.0);\n"
        "}";

    // compiler le shader de dessin
    m_ShaderId = Utils::makeShaderProgram(srcVertexShader, srcFragmentShader, "Tetraedre");

    // déterminer où sont les variables attribute et uniform
    m_PMatrixLoc = glGetUniformLocation(m_ShaderId, "mat4Projection");
    m_MVMatrixLoc = glGetUniformLocation(m_ShaderId, "mat4ModelView");
    m_VertexLoc = glGetAttribLocation(m_ShaderId, "glVertex");
    m_ColorLoc = glGetAttribLocation(m_ShaderId, "glColor");

    /** VBOs */

    // créer et remplir le buffer des coordonnées
    const float b = 0.5;
    std::vector<GLfloat> vertices {
        -b, +b, +b,     // P0 bleu
        +b, -b, +b,     // P1 orange
        +b, +b, -b,     // P2 vert
        -b, -b, -b,     // P3 violet
    };
    m_VertexBufferId = Utils::makeFloatVBO(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    // créer et remplir le buffer des couleurs
    std::vector<GLfloat> colors {
        0.0, 0.5, 1.0,  // P0 bleu
        1.0, 0.5, 0.0,  // P1 orange
        0.0, 1.0, 0.0,  // P2 vert
        0.7, 0.0, 0.7,  // P3 violet
    };
    m_ColorBufferId = Utils::makeFloatVBO(colors, GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    // créer et remplir le buffer des indices
    std::vector<GLushort> indexlist {
        0, 1,
        0, 2,
        0, 3,
        1, 2,
        1, 3,
        2, 3,
    };
    m_IndexBufferId = Utils::makeShortVBO(indexlist, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}


/**
 * dessiner le tétraèdre
 * @param mat4Projection : matrice de projection
 * @param mat4ModelView : matrice de vue
 */
void Tetraedre::onDraw(mat4 mat4Projection, mat4 mat4ModelView)
{
    // activer le shader
    glUseProgram(m_ShaderId);

    // fournir les matrices P et MV au shader
    mat4::glUniformMatrix(m_PMatrixLoc, mat4Projection);
    mat4::glUniformMatrix(m_MVMatrixLoc, mat4ModelView);

    // activer et lier le buffer contenant les coordonnées
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glEnableVertexAttribArray(m_VertexLoc);
    glVertexAttribPointer(m_VertexLoc, Utils::VEC3, GL_FLOAT, GL_FALSE, 0, 0);

    // activer et lier le buffer contenant les couleurs
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
    glEnableVertexAttribArray(m_ColorLoc);
    glVertexAttribPointer(m_ColorLoc, Utils::VEC3, GL_FLOAT, GL_FALSE, 0, 0);

    // activer et lier le buffer contenant les indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);

    // dessiner les lignes
    glLineWidth(3.0);
    glDrawElements(GL_LINES, LINE_COUNT * 2, GL_UNSIGNED_SHORT, 0);

    // désactiver les buffers
    glDisableVertexAttribArray(m_VertexLoc);
    glDisableVertexAttribArray(m_ColorLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // désactiver le shader
    glUseProgram(0);
}


/**
 * Cette méthode supprime les ressources allouées
 */
Tetraedre::~Tetraedre()
{
    Utils::deleteVBO(m_IndexBufferId);
    Utils::deleteVBO(m_ColorBufferId);
    Utils::deleteVBO(m_VertexBufferId);
    Utils::deleteShaderProgram(m_ShaderId);
}
