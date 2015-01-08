


function getDim() {
	dim = document.getElementById("dim").value;
	node = document.getElementById("stub");
	node.innerHTML = ""; // alte Tabelle löschen
	node.appendChild(genMatrix(dim)); 
	if(document.getElementById("checkbox-gen").checked==true) {
		if(dim==1) {
			document.getElementById("x1").value = 1;
		} else 
		if(dim==2) {
			document.getElementById("x1").value = 2;
			document.getElementById("x2").value = 5;
			document.getElementById("x3").value = 1;
			document.getElementById("x4").value = 3;
		} else 
		if(dim==3) {
			document.getElementById("x1").value = 1;
			document.getElementById("x2").value = 2;
			document.getElementById("x3").value = 0;
			document.getElementById("x4").value = 2;
			document.getElementById("x5").value = 4;
			document.getElementById("x6").value = 1;
			document.getElementById("x7").value = 2;
			document.getElementById("x8").value = 1;
			document.getElementById("x9").value = 0;
		} else 
		if(dim==4) {
			document.getElementById("x1").value = 4;
			document.getElementById("x2").value = 0;
			document.getElementById("x3").value = 0;
			document.getElementById("x4").value = 0;
			document.getElementById("x5").value = 0;
			document.getElementById("x6").value = 0;
			document.getElementById("x7").value = 2;
			document.getElementById("x8").value = 0;
			document.getElementById("x9").value = 0;
			document.getElementById("x10").value = 1;
			document.getElementById("x11").value = 2;
			document.getElementById("x12").value = 0;
			document.getElementById("x13").value = 1;
			document.getElementById("x14").value = 0;
			document.getElementById("x15").value = 0;
			document.getElementById("x16").value = 1;
		} else 
		if(dim==5) {
			document.getElementById("x1").value = 1;
			document.getElementById("x2").value = 8;
			document.getElementById("x3").value = -9;
			document.getElementById("x4").value = 7;
			document.getElementById("x5").value = 5;
			document.getElementById("x6").value = 0;
			document.getElementById("x7").value = 1;
			document.getElementById("x8").value = 0;
			document.getElementById("x9").value = 4;
			document.getElementById("x10").value = 4;
			document.getElementById("x11").value = 0;
			document.getElementById("x12").value = 0;
			document.getElementById("x13").value = 1;
			document.getElementById("x14").value = 2;
			document.getElementById("x15").value = 5;
			document.getElementById("x16").value = 0;
			document.getElementById("x17").value = 0;
			document.getElementById("x18").value = 0;
			document.getElementById("x19").value = 1;
			document.getElementById("x20").value = -5;
			document.getElementById("x21").value = 0;
			document.getElementById("x22").value = 0;
			document.getElementById("x23").value = 0;
			document.getElementById("x24").value = 0;
			document.getElementById("x25").value = 1;

		}
		else {
			alert("Kann max. 5x5 Matrizen generieren!");
		}
		document.getElementById("checkbox-gen").checked = false; // zurücksetzen 
	}
}


function genMatrix(dim) { // Rückgabewert ist die generierte HTML-Tabelle
	// ein Formular erzeugen: 
	var form = document.createElement("form"); 
	form.setAttribute("id", "inputmatrix");
	form.setAttribute("action", "http://maltin.pisces.uberspace.de/cgi-bin/matrix.cgi");
	form.setAttribute("method", "post");
	var hiddenInfo = document.createElement("input");
	hiddenInfo.setAttribute("type","hidden");
	hiddenInfo.setAttribute("name", "dimension");
	hiddenInfo.setAttribute("value", dim);
	form.appendChild(hiddenInfo);
	// Eingaben verifizieren:
	form.onsubmit = function() {
		// hier testen, ob alle felder ausgefüllt sind
		for(var i=0; i<(dim*dim); i++) {
			var id = "x" + (i+1);
			if(document.getElementById(id).value == "") {
				alert("bitte das Feld " + (i+1) + " ausfüllen!");
				return false;
			}
		} 
	}

	// Eingabemaske bauen: 
	tab = document.createElement("table");
	for(var row=0; row<dim; row++) {
		var crow = document.createElement("tr");
		for(var col=0; col<dim; col++) {
			var cell = document.createElement("td");

			var cell_input = document.createElement("input");
			cell_input.setAttribute("id", "x"+(row*dim+col+1));
			cell_input.setAttribute("name", cell_input.getAttribute("id"));
			cell.appendChild(cell_input);
			crow.appendChild(cell);
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