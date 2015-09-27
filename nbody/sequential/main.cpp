#include <diego/glfw/include/GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>

struct Vector {
    float x, y, z;
};

struct Body {
    Vector position;
    float m;
    Vector velocity;
};

void update_bodies(std::vector<Body> &bodies) {
    float eps = 0.0001f;
    float dt = 0.01f;

    std::vector<Vector> new_positions(bodies.size());

    for (int i = 0; i < bodies.size(); ++i) {
        Vector a = {0.f, 0.f, 0.f};

        for (int j = 0; j < bodies.size(); ++j) {
            Vector d = {
                    bodies[j].position.x - bodies[i].position.x,
                    bodies[j].position.y - bodies[i].position.y,
                    bodies[j].position.z - bodies[i].position.z
            };
            float invr = 1.0 / sqrt(d.x * d.x + d.y * d.y + d.z * d.z + eps);
            float invr3 = invr * invr * invr;
            float f = bodies[j].m * invr3;
            a.x += f * d.x;
            a.y += f * d.y;
            a.z += f * d.z;
        }

        new_positions[i].x = bodies[i].position.x + dt * bodies[i].velocity.x + 0.5f * dt * dt * a.x;
        new_positions[i].y = bodies[i].position.y + dt * bodies[i].velocity.y + 0.5f * dt * dt * a.y;
        new_positions[i].z = bodies[i].position.z + dt * bodies[i].velocity.z + 0.5f * dt * dt * a.z;
        bodies[i].velocity.x += dt * a.x;
        bodies[i].velocity.y += dt * a.y;
        bodies[i].velocity.z += dt * a.z;
    }

    for (int i = 0; i < bodies.size(); ++i) {
        bodies[i].position = new_positions[i];
    }
}

int main(void)
{
    std::vector<Body> bodies {
            {{0.f, 0.f, 0.f}, 0.5f, {0.f, 0.f, 0.f}},
            {{0.5f, 0.f, 0.f}, 0.f, {0.f, 1.f, 0.f}}
    };

    GLFWwindow* window;
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(1024, 1024, "Sequential N-Body", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        update_bodies(bodies);

        for (int i = 0; i < bodies.size(); ++i) {
            glPointSize(bodies[i].m);
            glBegin(GL_POINTS);
            glColor3f(1.f, 1.f, 1.f);
            glVertex3f(bodies[i].position.x, bodies[i].position.y, bodies[i].position.z);
            glEnd();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

