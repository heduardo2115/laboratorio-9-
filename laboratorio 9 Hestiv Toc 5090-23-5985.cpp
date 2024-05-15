#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};


class Stack {
private:
    Node* top;
public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int peek() const {
        if (top != nullptr) {
            return top->data;
        }
        throw std::runtime_error("Stack is empty");
    }
};






class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (front != nullptr) {
            dequeue();
        }
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front != nullptr) {
            Node* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int peek() const {
        if (front != nullptr) {
            return front->data;
        }
        throw std::runtime_error("Queue is empty");
    }
};


void displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Agregar tarea\n";
    std::cout << "2. Completar última tarea\n";
    std::cout << "3. Atender tarea más antigua\n";
    std::cout << "4. Mostrar todas las tareas\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opción: ";
}

void showAllTasks(const Stack& stack, const Queue& queue) {
    std::cout << "Tareas (de más antigua a más reciente):\n";
    Queue tempQueue = queue;
    while (!tempQueue.isEmpty()) {
        std::cout << tempQueue.peek() << "";
        tempQueue.dequeue();
    }
    Stack tempStack = stack;
    while (!tempStack.isEmpty()) {
        std::cout << tempStack.peek() << "";
        tempStack.pop();
    }
    std::cout << std::endl;
}

int main() {
    Stack stack;
    Queue queue;
    int option, task;

    do {
        displayMenu();
        std::cin >> option;

        switch (option) {
            case 1:
                std::cout << "Ingrese la nueva tarea: ";
                std::cin >> task;
                stack.push(task);
                queue.enqueue(task);
                break;
            case 2:
                if (!stack.isEmpty()) {
                    stack.pop();
                } else {
                    std::cout << "No hay tareas para completar.\n";
                }
                break;
            case 3:
                if (!queue.isEmpty()) {
                    queue.dequeue();
                } else {
                    std::cout << "No hay tareas para atender.\n";
                }
                break;
            case 4:
                showAllTasks(stack, queue);
                break;
            case 5:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (option != 5);

    return 0;
}
