function draw() {
    let nodes = getNodes();
    let edges = getEdges(nodes);

    nodes = makeDfs(nodes, edges);

    drawNetwork(nodes, edges);
}

function drawNetwork(nodes, edges) {
    const container = document.getElementById('mynetwork');
    const data = {
        nodes: nodes,
        edges: edges
    };
    var options = {
        layout: {
            hierarchical: {
                direction: 'LR'
            }
        }
    };
    var network = new vis.Network(container, data, options);
}

function getNodes() {
    let nodes = [];

    for (let i = 0; i < disciplines.length; i++)
        nodes.push({
            id: i,
            label: disciplines[i],
            color: 'gray',
            shape: 'circle',
            borderWidth: disciplines[i] === 'DCC203' ? 3 : ''
        });

    return nodes;
}

function getNodeId(nodes, label) {
    for (let i = 0; i < nodes.length; i++)
        if (nodes[i].label === label)
            return nodes[i].id;
    return null;
}

function getEdges(nodes) {
    let edges = [];

    for (let i = 0; i < prerequisites.length; i++) {
        edges.push({
            id: i,
            from: getNodeId(nodes, prerequisites[i].from),
            to: getNodeId(nodes, prerequisites[i].to),
            arrows: 'to'
        });
    }

    return edges;
}

function makeDfs(nodes, edges) {

    const ans = makevg(nodes, edges);
    let v1 = ans.v.slice();
    let g1 = ans.g.slice();
    const i1 = getNodeId(nodes, 'DCC203');
    dfs(v1, g1, i1, 1);

    let v2 = ans.v.slice();
    let g2 = ans.g.slice();
    const i2 = getNodeId(nodes, 'MAT001');
    dfs(v2, g2, i2, 2);

    for (let i = 0; i < nodes.length; i++) {
        if (v1[i] === 1 && v2[i] === 2)
            nodes[i].color = 'green';
        else if (v1[i] === 1)
            nodes[i].color = 'red';
        else if (v2[i] === 2)
            nodes[i].color = 'blue';
    }

    return nodes;
}

function makevg(nodes, edges) {
    let v = [];
    let g = [];

    for (let i = 0; i < nodes.length; i++) {
        v.push(0);
        let g1 = [];
        for (let j = 0; j < nodes.length; j++)
            g1.push(0);
        g[i] = [];
        g[i].push(g1);
    }

    for (let i = 0; i < edges.length; i++) {
        const f = edges[i].from;
        const t = edges[i].to;
        g[f][t] = 1;
    }

    return { v, g };
}

function dfs(v, g, i, c) {
    v[i] += c;

    for (let k = 0; k < v.length; k++) {
        if (v[k] == 0 && g[i][k] == 1)
            dfs(v, g, k, c);
    }
}


