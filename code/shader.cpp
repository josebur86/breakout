
Shader & Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
    if (useShader)
    {
        this->Use();
    }

    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
