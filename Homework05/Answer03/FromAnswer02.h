#pragma once

class I3DAPI
{
public:
    virtual ~I3DAPI() {}
    virtual std::string draw() const = 0;
};


class OpenGL_api : public I3DAPI
{
public:
    std::string draw() const override { return "using OpenGL to draw"; }
};


class DirectX_api : public I3DAPI
{
public:
    std::string draw() const override { return "using DirectX to draw"; }
};


class Shape
{
    I3DAPI* renderer;

public:
    Shape(I3DAPI* api) : renderer(api) {}
    virtual ~Shape() {}

    std::string draw() const { return renderer->draw(); }
};


class Triangle : public Shape
{
public:
    Triangle(I3DAPI* api) : Shape(api) {}
};


class Circle : public Shape
{
public:
    Circle(I3DAPI* api) : Shape(api) {}
};

