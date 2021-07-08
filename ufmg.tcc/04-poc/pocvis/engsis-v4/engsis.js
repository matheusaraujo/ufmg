function draw() {
    let nodes = getNodes();
    let edges1 = getEdges1(nodes);
    let edges2 = getEdges2(nodes, edges1.length);

    let edges = edges1.concat(edges2);

    nodes = makeDfs(nodes, edges1);

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
            label: disciplines[i].label,
            level: disciplines[i].level,
            shape: 'circle',
            color: '#b3b3b3'
        });

    return nodes;
}

function getNodeId(nodes, label) {
    for (let i = 0; i < nodes.length; i++)
        if (nodes[i].label === label)
            return nodes[i].id;
    return null;
}

function getEdges1(nodes) {
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

function getEdges2(nodes, te) {
    let edges = [];

    for (let i = 0; i < prerequisites2.length; i++) {
        edges.push({
            id: te + i,
            from: getNodeId(nodes, prerequisites2[i].from),
            to: getNodeId(nodes, prerequisites2[i].to),
            hidden: true
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

    let cnt = 0;

    for (let i = 0; i < nodes.length; i++) {
        if (v1[i] === 1 && v2[i] === 2)
            cnt++ , nodes[i].color = '#8da0cb';
        else if (v1[i] === 1)
            cnt++ , nodes[i].color = '#66c2a5';
        else if (v2[i] === 2)
            cnt++ , nodes[i].color = '#e78ac3';
    }

    console.log('Total: ' + v1.length);
    console.log('DCC203: ' + v1.filter(v => v > 0).length);
    console.log('MAT001: ' + v2.filter(v => v > 0).length);
    console.log('DCC203 && MAT001: ' + cnt);

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


