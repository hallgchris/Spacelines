function submitMove(x, y, z) {
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "/move", true);
    xhr.setRequestHeader('Content-Type', "application/x-www-form-urlencoded");
    xhr.send(`x=${x}&y=${y}&z=${z}`);
}

function createMoveTable(side_length, z = 0) {
    let tableHtml = "";
    for (let y = 0; y < side_length; y++) {
        tableHtml += "<tr>";
        for (let x = 0; x < side_length; x++) {
            tableHtml += `<td><button onclick="submitMove(${x}, ${y}, ${z})">${x}, ${y}, ${z}</button></td>`;
        }
        tableHtml += "</tr>";
    }
    return tableHtml;
}

function createMoveTables(side_length, dimensions) {
    let tableHtml = "";

    if (dimensions === 3)
        for (let z = side_length - 1; z >= 0; z--)
            tableHtml += `<p>Layer ${z}</p><table>${createMoveTable(side_length, z)}</table>`;
    else if (dimensions === 2)
        tableHtml += `<table>${createMoveTable(side_length)}</table>`;
    else
        console.log(`Invalid dimension: ${dimensions}`);

    document.getElementById("moveTables").innerHTML = tableHtml;
}

let xhr = new XMLHttpRequest();

// Called whenever the readyState attribute changes
xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
        let jsonData = JSON.parse(xhr.responseText);
        createMoveTables(Number(jsonData.size), Number(jsonData.dimensions));
    }
};

xhr.open("GET", "/getsize", true);
xhr.send();
