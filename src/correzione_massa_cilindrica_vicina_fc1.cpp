#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <numeric>
#include <fstream>
// dst centro sfera - centro cilindro
double constexpr b = 0.04747;
double constexpr M = 2.757;
double constexpr R = 0.033907917;
double constexpr H = 0.06987;
const char* output_filepath = "./output/results_correzione_massa_vicina_fc1.txt";

int constexpr X_WIDTH_DIVISIONS = 500;
int constexpr Y_LENGHT_DIVISIONS = 500;
int constexpr Z_HEIGHT_DIVISIONS = 500;
struct Vector3
{
    double x;
    double y;
    double z;
};
double norm2(Vector3 const &pos)
{
    return pos.x * pos.x +
           pos.y * pos.y +
           pos.z * pos.z;
}

double norm(Vector3 const &pos)
{
    return std::sqrt(norm2(pos));
}

struct Particle
{
    Vector3 position;
    double mass;
};

struct Body
{
    std::vector<Particle> particles;
};

Vector3 operator-(Vector3 const &lhs, Vector3 const &rhs)
{
    return Vector3{
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z};
}

Vector3 operator/(Vector3 const &lhs, double rhs)
{
    return Vector3{
        lhs.x / rhs,
        lhs.y / rhs,
        lhs.z / rhs};
}

constexpr int CountParticles()
{
    int sum{0};
    for (double x = -R; x <= +R; x += R / X_WIDTH_DIVISIONS)
    {
        for (double y = -R; y <= +R; y += R / Y_LENGHT_DIVISIONS)
        {
            for (double z = -H / 2.; z <= +H / 2; z += H / Z_HEIGHT_DIVISIONS)
            {
                if (x * x + y * y <= R * R)
                {
                    ++sum;
                }
            }
        }
    }
    return sum;
}


int main()
{
    Body massa_sorgente;

    std::cout<<"counting particles..."<<std::endl;
    int number_of_particles{CountParticles()};
    double mass_of_one_particle{M / number_of_particles};

    std::cout<< "calculating the sum..."<<std::endl;
    Vector3 posizione_massa_sferica{b, 0., 0.};
    double sum{0};
    for (double x = -R; x <= +R; x += R / X_WIDTH_DIVISIONS)
    {
        for (double y = -R; y <= +R; y += R / Y_LENGHT_DIVISIONS)
        {
            for (double z = -H / 2.; z <= +H / 2; z += H / Z_HEIGHT_DIVISIONS)
            {
                if (x * x + y * y <= R * R)
                {
                    Particle particle{{x, y, z}, mass_of_one_particle};
                    Vector3 r{posizione_massa_sferica - particle.position};
                    Vector3 r_versor = r / norm(r);
                    sum += (particle.mass / norm2(r)) * r_versor.x;
                }
            }
        }
    }

    std::cout<<"finished!"<<std::endl;
    std::cout << "number of particles = " << number_of_particles << '\n';
    std::cout << "fc1 = F/Fs =  " << std::setprecision(15) << (b * b / M) * sum << '\n';
    std::cout << "the results have also been written in "<<output_filepath<<std::endl;

    std::ofstream output{output_filepath, std::ios::out|std::ios::trunc};
    output << "x_radius_divisions = "<<X_WIDTH_DIVISIONS<<'\n';
    output << "y_radius_divisions = "<<Y_LENGHT_DIVISIONS<<'\n';
    output << "z_height_divisions = "<<Z_HEIGHT_DIVISIONS<<'\n';
    output << "number of particles = " << number_of_particles << '\n';
    output << "fc1 = F/Fs = " << std::setprecision(15) << (b * b / M) * sum << '\n';

}