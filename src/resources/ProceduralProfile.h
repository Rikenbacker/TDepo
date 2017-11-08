//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include "../common/Vector2DFloat.h"

#include <string>
#include <vector>

class ProceduralProfile
{
    public:
        ProceduralProfile() = default;
        ~ProceduralProfile();

        /*!
         * Добавляет точку в хранилище точек
         * @param pt: точка
         * @return Номер точки в списке
         */
        unsigned short addPoint(TDC::Vector2DFloat pt);

        /*!
         * Возвращает указатель на массив точек
         * @return указатель на масстив точек
         */
        const TDC::Vector2DFloat *getPointsArray();

        /*!
         * Возвращает указатель на список точек
         * @return указатель на список точек
         */
        const std::vector<TDC::Vector2DFloat> *getPoints();

        /*!
         * Добавляет треугольник к отображению профиля объекта по индексам в массиве
         * \param a Порядковый номер в массиве точек первой точки
         * \param b Порядковый номер в массиве точек второй точки
         * \param c Порядковый номер в массиве точек третьей точки
         */
        void addTriangle(unsigned short a, unsigned short b, unsigned short c);

        /*!
         * Возвращает указатель на массив последовательностей точек для построения треугольников
         * @return указатель на массив последовательностей точек для построения треугольников
         */
        const unsigned short *getTrianglesArray();

        /*!
         * Возвращает длину списка точек для построения треугольников
         * @return длина списка точек для построения треугольников
         */
        unsigned long getTrianglesCount();

        //! Добавляет точку в список точек составляющих контур профиля
        /** \param positionPoint: порядковый номер точки в массиве */
        void addCircuitPoint(unsigned short positionPoint);

        /*!
         * Возвращает список индексов для построения треугольников профиля фигуры
         * @return указатель на список индексов точек массива
         */
        const std::vector<unsigned short> *getTriangles();

        /*!
         * Возвращает список точек составляющих контур профиля
         * @return указатель на список указателей на точки
         */
        const std::vector<unsigned short> *getCircuit();

    private:
        //Список внешних точек, для построения объема
        std::vector<TDC::Vector2DFloat> points;

        //Список точек кратный трём, для построения из треугольников профиля.
        std::vector<unsigned short> triangles;
        std::vector<unsigned short> circuit;
};