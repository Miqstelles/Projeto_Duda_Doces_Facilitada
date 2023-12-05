#include <stdbool.h>
#include "clientes.h"

bool pedidoPertenceAoCliente(int codigoPedido, cliente clnt) {
    for (int i = 0; i < 200 && clnt.pedidos[i] != 0; i++) {
        if (clnt.pedidos[i] == codigoPedido) return true;
    }
    return false;
}
