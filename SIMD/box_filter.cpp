#include "../base_func/timer.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

class SimpleMat
{
public:
    SimpleMat(int rows, int cols, int channels)
    {
        this->rows = rows;
        this->cols = cols;
        this->channels = channels;
        data_.resize(rows * cols * channels);
    }

    float operator[](int index) const
    {
        return data_[index];
    }

    float* data()
    {
        return data_.data();
    }

    int rows;
    int cols;
    int channels;
    std::vector<float> data_;
};

void BoxFilterOrigin(float* Src, float* Dest, int Width, int Height, int Radius)
{
    for (int Y = 0; Y < Height; Y++)
    {
        for (int X = 0; X < Width; X++)
        {
            int ST_Y = Y - Radius;
            if (ST_Y < 0)
                ST_Y = 0;
            int EN_Y = Y + Radius;
            if (EN_Y > Height - 1)
                EN_Y = Height - 1;
            int ST_X = X - Radius;
            if (ST_X < 0)
                ST_X = 0;
            int EN_X = X + Radius;
            if (EN_X > Width - 1)
                EN_X = Width - 1;
            float sum = 0;
            for (int ty = ST_Y; ty <= EN_Y; ty++)
            {
                for (int tx = ST_X; tx <= EN_X; tx++)
                {
                    sum += Src[ty * Width + tx];
                }
            }
            Dest[Y * Width + X] = sum;
        }
    }
}

void BoxFilterOpenCV(float* Src, float* Dest, int Width, int Height, int Radius, std::vector<float>& cache)
{
    float* cachePtr = &(cache[0]);
    // chuizhi
    for (int Y = 0; Y < Height; Y++)
    {
        for (int X = 0; X < Width; X++)
        {
            int ST_X = X - Radius;
            if (ST_X < 0)
                ST_X = 0;
            int EN_X = X + Radius;
            if (EN_X > Width - 1)
                EN_X = Width - 1;
            float sum = 0;
            for (int tx = ST_X; tx <= EN_X; tx++)
            {
                sum += Src[Y * Width + tx];
            }
            cachePtr[Y * Width + X] = sum;
        }
    }

    //shuiping
    for (int Y = 0; Y < Height; Y++)
    {
        int ST_Y = Y - Radius;
        if (ST_Y < 0)
            ST_Y = 0;
        int EN_Y = Y + Radius;
        if (EN_Y > Height - 1)
            EN_Y = Height - 1;
        for (int X = 0; X < Width; X++)
        {
            float sum = 0;
            for (int ty = ST_Y; ty <= EN_Y; ty++)
            {
                sum += cachePtr[ty * Width + X];
            }
            Dest[Y * Width + X] = sum;
        }
    }
}



// test
int main()
{
    int Width = 3024;
    int Height = 4032;
    SimpleMat Src(Width, Height, 1);
    SimpleMat Dest(Width, Height, 1);
    int Radius = 3;
    Timer t;
    BoxFilterOrigin(Src.data(), Dest.data(), Width, Height, Radius);
    std::vector<float> cache(Width * Height, 0);
    BoxFilterOpenCV(Src.data(), Dest.data(), Width, Height, Radius, cache);

    std::cout << "Time: μm " << t.elapsed() << std::endl;
    return 0;
}
