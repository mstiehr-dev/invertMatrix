


function getDim() {
	dim = document.getElementById("dim").value;
	node = document.getElementById("stub");
	node.innerHTML = ""; // alte Tabelle löschen 
	node.appendChild(genMatrix(dim));
}


function genMatrix(dim) { // Rückgabewert ist die generierte HTML-Tabelle
	// ein Formular erzeugen: 
	var form = document.createElement("form"); 
	form.setAttribute("id", "inputmatrix");
	form.setAttribute("action", "http://maltin.pisces.uberspace.de/cgi-bin/matrix.cgi");
	form.setAttribute("method", "GET");
	// Eingaben verifizieren:
	form.onsubmit = function() {
		// hier testen, ob alle felder ausgefüllt sind
		for(var i=0; i<(dim*dim); i++) {
			var id = "x" + i;
			if(document.getElementById(id).value == "") {
				alert("bitte das Feld " + (i+1) + " ausfüllen!");
				return false;
			}
		} 
	}

	// Eingabemaske bauen: 
	tab = document.createElement("table");
	tab.setAttribute("style", "border-style: solid; border-width: 5px");
	for(var row=0; row<dim; row++) {
		var crow = document.createElement("tr");
		for(var col=0; col<dim; col++) {
			var cell = document.createElement("td");

			var cell_input = document.createElement("input");
			cell_input.setAttribute("id", "x"+(row*dim+col));
			cell_input.setAttribute("name", cell_input.getAttribute("id"));
			//cell_input.setAttribute("value",cell_input.getAttribute("id"));
			cell_input.setAttribute("style", "height: 20px; width: 35px");
			cell.appendChild(cell_input);
			crow.appendChild(cell);
			/* '+' anhängen: 
			if(col<dim) {
				var label = document.createElement("label");
				label.innerHTML = "x<sub>" + (col+1) + "</sub>" + "+";
				crow.appendChild(label);
			} */
		}
		tab.appendChild(crow);
	}
	var submit = document.createElement("input");
	submit.setAttribute("type","submit");
	submit.setAttribute("value","calculate");
	var row = document.createElement("tr");
	var col = document.createElement("td");
	col.setAttribute("colspan",dim); // noch rechtsbündig machen mit css? 
	col.appendChild(submit);
	row.appendChild(col);
	tab.appendChild(row);
	form.appendChild(tab);
	return form;
}