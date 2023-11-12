#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Lista {
    struct Node* head;
    int size;
};

void initialize(struct Lista* lista) {
    lista->head = NULL;
    lista->size = 0;
}

bool isEmpty(struct Lista* lista) {
    return (lista->size == 0);
}

int getSize(struct Lista* lista) {
    return lista->size;
}

void display(struct Lista* lista) {
    struct Node* current = lista->head;
    printf("Elementos na lista: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

bool consultar(struct Lista* lista, int pos, int* value) {
    if (pos < 0 || pos >= lista->size)
        return false;

    struct Node* current = lista->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    *value = current->data;
    return true;
}

bool insert(struct Lista* lista, int value, int pos) {
    if (pos < 0 || pos > lista->size)
        return false;

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = value;
    if (pos == 0) {
        new_node->next = lista->head;
        lista->head = new_node;
    } else {
        struct Node* current = lista->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    lista->size++;
    return true;
}

bool alterar(struct Lista* lista, int value, int pos) {
    if (pos < 0 || pos >= lista->size)
        return false;

    struct Node* current = lista->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    current->data = value;
    return true;
}

bool removeElement(struct Lista* lista, int pos) {
    if (pos < 0 || pos >= lista->size)
        return false;

    struct Node* temp;
    if (pos == 0) {
        temp = lista->head;
        lista->head = temp->next;
    } else {
        struct Node* current = lista->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }
    free(temp);
    lista->size--;
    return true;
}

bool salvar(struct Lista* lista) {
    FILE* file = fopen("lista.txt", "w");
    if (file == NULL) {
        return false;
    }

    struct Node* current = lista->head;
    while (current != NULL) {
        fprintf(file, "%d\n", current->data);
        current = current->next;
    }

    fclose(file);
    return true;
}

bool carregar(struct Lista* lista) {
    FILE* file = fopen("lista.txt", "r");
    if (file == NULL) {
        return false;
    }

    initialize(lista);

    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        insert(lista, value, lista->size);
    }

    fclose(file);
    return true;
}

void reinicializar(struct Lista* lista) {
    struct Node* current = lista->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    initialize(lista);
}

int main() {
    struct Lista lista;
    initialize(&lista);
    int opcao, elemento, posicao;

    while (1) {
        printf("\nEscolha uma operação:\n");
        printf("1. Verificar Tamanho da ED\n");
        printf("2. Exibir Elementos da ED\n");
        printf("3. Consultar Elementos na ED\n");
        printf("4. Inserir Elemento na ED\n");
        printf("5. Alterar Elemento da ED\n");
        printf("6. Excluir Elemento da ED\n");
        printf("7. Salvar ED\n");
        printf("8. Carregar ED\n");
        printf("9. Reinicializar ED\n");
        printf("10. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Tamanho da ED: %d\n", getSize(&lista));
                break;
            case 2:
                display(&lista);
                break;
            case 3:
                printf("Digite a posição a ser consultada: ");
                scanf("%d", &posicao);
                if (consultar(&lista, posicao, &elemento)) {
                    printf("Elemento na posição %d: %d\n", posicao, elemento);
                } else {
                    printf("Posição inválida ou lista vazia.\n");
                }
                break;
            case 4:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &elemento);
                printf("Digite a posição de inserção: ");
                scanf("%d", &posicao);
                if (insert(&lista, elemento, posicao)) {
                    printf("Elemento inserido com sucesso.\n");
                } else {
                    printf("Falha ao inserir elemento.\n");
                }
                break;
            case 5:
                printf("Digite o novo valor: ");
                scanf("%d", &elemento);
                printf("Digite a posição a ser alterada: ");
                scanf("%d", &posicao);
                if (alterar(&lista, elemento, posicao)) {
                    printf("Elemento alterado com sucesso.\n");
                } else {
                    printf("Falha ao alterar elemento.\n");
                }
                break;
            case 6:
                printf("Digite a posição a ser excluída: ");
                scanf("%d", &posicao);
                if (removeElement(&lista, posicao)) {
                    printf("Elemento excluído com sucesso.\n");
                } else {
                    printf("Falha ao excluir elemento.\n");
                }
                break;
            case 7:
                if (salvar(&lista)) {
                    printf("ED salva com sucesso.\n");
                } else {
                    printf("Falha ao salvar ED.\n");
                }
                break;
            case 8:
                if (carregar(&lista)) {
                    printf("ED carregada com sucesso.\n");
                } else {
                    printf("Falha ao carregar ED.\n");
                }
        }
    }
}