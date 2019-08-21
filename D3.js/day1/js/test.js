import * as d3 from "d3/d3.js";

var width = 6;
var height = 6;

var nodes = [
    { name: "0"},
    { name: "1"},
    { name: "2"},
    { name: "3"},
    { name: "4"},
    { name: "5"},
    { name: "6"}
];

var edges = [
    { source: 0, target: 1},
    { source: 0, target: 2},
    { source: 0, target: 3},
    { source: 1, target: 4},
    { source: 1, target: 5},
    { source: 1, target: 6}
];

var force = d3.layout.force()
                .nodes(nodes)
                .links(edges)
                .size([width, height])
                .linkDistance(90)
                .charge(-400);
force.start();

console.log(nodes);
console.log(edges);