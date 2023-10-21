package praticaprim;

import java.util.*;
import java.util.LinkedList;

public class PraticaPrim {

   
    public static void main(String[] args) {
        
        Scanner entrada = new Scanner(System.in);

        LinkedList<LinkedList<Integer>> adj = new LinkedList<LinkedList<Integer>>(); //lista de adjacencia
        criaGrafo(adj);

        ArrayList<Integer> T = new ArrayList<Integer>();    //lista de verticas percorridos

        System.out.println("Digite o vértice de partida: ");
        int node = entrada.nextInt();

        if (node < adj.size() - 1) { //verifica se vértice digitado está no grafo

            T.add(node); //adiciona vertice digitado na lista de percorridos

            ArrayList<Integer> AGM = algPrim(T, adj); //chama funçao do prim

            valorAGM(AGM); //função para calcular valor agm
            imprimeAGM(AGM); //imprime agm

        } else {
            System.out.println("Vértice digitado não pertence ao grafo");
        }

    }

    public static void valorAGM(ArrayList<Integer> AGM) {

        int soma = 0;

        for (int i = 2; i < AGM.size(); i += 3) { //soma os pesos das arestas da agm
            soma += AGM.get(i);
        }

        System.out.println("Valor do custo da AGM:" + soma);
    }

    public static void imprimeAGM(ArrayList<Integer> AGM) {

        System.out.println("Arestas da AGM: ");
        int i = 0;
        while (i < AGM.size()) { //imprime arestas da agm
            System.out.println(AGM.get(i) + " -> " + AGM.get(i + 1) + " " + AGM.get(i + 2));
            i += 3;
        }

    }

    public static ArrayList<Integer> algPrim(ArrayList<Integer> T, LinkedList<LinkedList<Integer>> adj) {

        ArrayList<Integer> AGM = new ArrayList<Integer>();

        while (T.size() != adj.size()){//repete algoritmo até todos os vertices serem percorridos

            int node = T.get(T.size() - 1); //pega vertice do topo da lista de percorridos
            removeT(node, adj); //chama função para remover arestas q chegam ao nó percorrido

            int menor = 999;

            int i = 0,origem=0,destino=0;
            int tamT = T.size();  //verifica tamanho da lista de percorridos
            while (i < tamT) {      //percorre lista de percorridos
                int vertOrigem = T.get(i);   //seleciona vertice de origem

                int j = 0;
                int tamAdj = adj.get(vertOrigem).size();//verifica tamanho da lista de adjacencia

                while (j < tamAdj) {//percorre lista de adjacencia

                    int vertDestino = adj.get(vertOrigem).get(j); //seleciona vertice de destino 
                    int peso = adj.get(vertOrigem).get(j + 1);     // e seu peso
                    
                    if (peso < menor) {     //compara os vertices para encontrar o que tem menor peso
                            menor = peso;
                            origem=vertOrigem;
                            destino=vertDestino;
                    }
                    j += 2;
                }
                i++;
            }
            
            AGM.add(origem); //adiciona vertice e aresta na AGM
            AGM.add(destino);
            AGM.add(menor);

            T.add(destino);

        }

        return AGM;
    }

    public static void removeT(int node, LinkedList<LinkedList<Integer>> adj) {

        for (int i = 0; i < adj.size(); i++) {      //percorre toda lista de adjacencia
            int pos = adj.get(i).indexOf(node);
            if (pos != -1) {
                adj.get(i).remove(pos + 1);   //remove vertice percorrido e respectivo peso 
                adj.get(i).remove(pos);     //da lista de adjacencia
            }
        }
    }
    
    public static void criaGrafo(LinkedList<LinkedList<Integer>> adj) {
        int V = 8;

        for (int i = 0; i < V; ++i) {   //cria lista encadeada
            adj.add(new LinkedList<>());
        }

        // Inserting nodes
        // Custom input node elements
        addEdge(adj, 1, 2, 36);      //adiciona vertices
        addEdge(adj, 1, 3, 29);
        addEdge(adj, 1, 5, 32);
        addEdge(adj, 1, 7, 19);
        addEdge(adj, 5, 4, 35);
        addEdge(adj, 7, 4, 37);
        addEdge(adj, 7, 5, 28);
        addEdge(adj, 0, 7, 16);
        addEdge(adj, 0, 4, 38);
        addEdge(adj, 2, 3, 17);
        addEdge(adj, 0, 2, 26);
        addEdge(adj, 7, 2, 34);
        addEdge(adj, 2, 6, 40);
        addEdge(adj, 3, 6, 52);
        addEdge(adj, 0, 6, 58);
        addEdge(adj, 6, 4, 93);
    }

    public static void addEdge(LinkedList<LinkedList<Integer>> Adj, int u, int v, int x) {
        // Creating bi-directional vertex
        Adj.get(u).add(v);      //adiciona adjacencia de vertice e seus pesos não-direcionalmente
        Adj.get(u).add(x);
        Adj.get(v).add(u);
        Adj.get(v).add(x);
    }

}
