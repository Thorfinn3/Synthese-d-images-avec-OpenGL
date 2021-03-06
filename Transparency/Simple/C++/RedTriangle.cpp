// Définition de la classe RedTriangle

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>
#include <math.h>

#include <utils.h>

#include <RedTriangle.h>



/** constructeur */
RedTriangle::RedTriangle() throw (std::string)
{
    /// Shader
    const char* srcVertexShader =
        "#version 300 es\n"
        "in vec2 glVertex;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(glVertex, 0.0, 1.0);\n"
        "}";

    const char* srcFragmentShader =
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 glFragColor;\n"
        "void main()\n"
        "{\n"
        "    glFragColor = vec4(0.84, 0.15, 0.51, 1.0);\n"
        "}";

    // compiler le shader de dessin
    m_ShaderId = Utils::makeShaderProgram(srcVertexShader, srcFragmentShader, "RedTriangle");

    // déterminer où sont les variables attribute
    m_VertexLoc = glGetAttribLocation(m_ShaderId, "glVertex");

    /** VBOs */

    // créer et remplir le buffer des coordonnées
    std::vector<GLfloat> vertices {
        -0.88, +0.52,       // P0
        +0.63, -0.79,       // P1
        +0.14, +0.95,       // P2
    };
    m_VertexBufferId = Utils::makeFloatVBO(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
}


/** dessiner l'objet */
void RedTriangle::onDraw()
{
    // activer le shader
    glUseProgram(m_ShaderId);

    // activer et lier le buffer contenant les coordonnées
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glEnableVertexAttribArray(m_VertexLoc);
    glVertexAttribPointer(m_VertexLoc, Utils::VEC2, GL_FLOAT, GL_FALSE, 0, 0);

    // dessiner un triangle avec les trois vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // désactiver le buffer
    glDisableVertexAttribArray(m_VertexLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // désactiver le shader
    glUseProgram(0);
}


/** destructeur */
RedTriangle::~RedTriangle()
{
    // supprimer les buffers et le shader
    Utils::deleteShaderProgram(m_ShaderId);
    Utils::deleteVBO(m_VertexBufferId);
}
