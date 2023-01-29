#pragma once

#include <concepts>
#include <functional>
#include <iostream>
#include <memory>

class Circle
{
public:
    explicit Circle(double red) : radius(red)
    {
    }

    double getRadius() const noexcept { return radius; }

private:
    double radius;
};

class Square
{
public:
    explicit Square(double s) : side(s)
    {
    }

    double getSide() const noexcept { return side; }

private:
    double side;
};

class Shape
{
private:
    struct ShapeConcept
    {
        virtual ~ShapeConcept() = default;

        virtual void do_serialize() const = 0;
        virtual void do_draw() const = 0;
        virtual std::unique_ptr<ShapeConcept> clone() const = 0;
    };

    template <typename ShapeT>
    struct ShapeModel : public ShapeConcept
    {
        ShapeModel(ShapeT shape) : shape_{std::move(shape)} {}

        void do_serialize() const override
        {
            serialize(shape_);
        }

        void do_draw() const override
        {
            draw(shape_);
        }

        std::unique_ptr<ShapeConcept> clone() const override
        {
            return std::make_unique<ShapeModel>(*this);
        }

        ShapeT shape_;
    };

    std::unique_ptr<ShapeConcept> pimpl;

public:
    template <typename ShapeT>
    Shape(ShapeT shape) : pimpl{std::make_unique<ShapeModel<ShapeT>>(std::move(shape))}
    {
    }

    template <typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer) : pimpl{std::make_unique<ExtendedModel<ShapeT, DrawStrategy>>(std::move(shape), std::move(drawer))}
    {
    }

    friend void serialize(Shape const& shape)
    {
        shape.pimpl->do_serialize();
    }
    friend void draw(Shape const& shape)
    {
        shape.pimpl->do_draw();
    }

    // copy operators
    Shape(Shape const& other) : pimpl(other.pimpl->clone()) {}
    Shape& operator=(Shape const& other)
    {
        Shape tmp(other);
        std::swap(pimpl, tmp.pimpl);
        return *this;
    }

    // move operators
    //    Shape(Shape&& other) = default;
    Shape& operator=(Shape&& other) noexcept
    {
        pimpl.swap(other.pimpl);
        return *this;
    }

    template <typename ShapeT, typename DrawStrategy>
    struct ExtendedModel : public ShapeConcept
    {
        explicit ExtendedModel(ShapeT shape, DrawStrategy drawer) : shape_(std::move(shape)), drawer_(std::move(drawer)) {}

        void do_serialize() const override
        {
            serialize(shape_);
        }

        void do_draw() const override
        {
            drawer_(shape_);
        }

        std::unique_ptr<ShapeConcept> clone() const override
        {
            return std::make_unique<ExtendedModel>(*this);
        }

    private:
        ShapeT shape_;
        DrawStrategy drawer_;
    };
};

void serialize(Circle const&) {}
void draw(Circle const& circle)
{
    std::cout << "drawing circle with r of " << circle.getRadius() << std::endl;
}

void serialize(Square const&) {}
void draw(Square const& square)
{
    std::cout << "drawing square with w of " << square.getSide() << std::endl;
}

void drawAllShapes(std::vector<Shape> const& shapes)
{
    for (auto const& shape : shapes)
    {
        draw(shape);
    }
}
