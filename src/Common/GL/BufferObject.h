#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

template<typename T>
class BufferObject {

private:
    unsigned int _id;
    int _type;
    std::vector<T> * _data;

public:
    BufferObject( int type, std::vector<T> * data);
    ~BufferObject();

    void Bind() const;
    void Unbind() const;
    void BufferData() const;
    void SetAttribPointer(unsigned int vao, int dtype) const;

    inline std::vector<T> * GetVector() const {return _data; }
    inline std::vector<T> * GetSize() const {return _data->size(); }

};

template<typename T>
BufferObject<T>::BufferObject(int type, std::vector<T> * data) {
    if (!!data)
        _data = data;
    else
        _data = new std::vector<T>();

    _type = type;
    
    glGenBuffers(1, &_id);
}

template<typename T>
BufferObject<T>::~BufferObject() {
    glDeleteBuffers(1, &_id);
}

template<typename T>
void BufferObject<T>::Bind() const {
    glBindBuffer(_type, _id);
}

template<typename T>
void BufferObject<T>::Unbind() const {
    glBindBuffer(_type, 0);
}

template<typename T>
void BufferObject<T>::BufferData() const {
    Bind();

    glBufferData(_type, _data->size() * sizeof(T), _data->data(), GL_STATIC_DRAW);

    Unbind();
}

template<typename T>
void BufferObject<T>::SetAttribPointer(unsigned int vao, int dtype) const {
    Bind();

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    switch(dtype) {
        case GL_FLOAT: 
            glVertexAttribPointer(0, sizeof(T) / sizeof(float), dtype, GL_FALSE, sizeof(T), nullptr);
            break;

        case GL_DOUBLE: 
            glVertexAttribPointer(0, sizeof(T) / sizeof(double), dtype, GL_FALSE, sizeof(T), nullptr);
            break;
    }
    
    glBindVertexArray(0);

    Unbind();
}
