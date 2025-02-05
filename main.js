var hoverMode = true;

function ToggleHoverMode(){
	hoverMode = !hoverMode;
	if(hoverMode){ document.getElementById("hoverModeButton").classList.add("Toggled"); }
	else{ document.getElementById("hoverModeButton").classList.remove("Toggled"); }
}

function DisplaySectionBody(section, typeOfDisplay){
	section.getElementsByClassName("SectionBody")[0].style.display = typeOfDisplay;
}

function Section(ids){
	ids.forEach(sectionId => {
		let section = document.getElementById(sectionId);

		if(section){
			let divs = section.getElementsByTagName("div");

			if (divs.length>1){
				section.classList.add("Section")
				divs[0].classList.add("SectionHead");
				divs[1].classList.add("SectionBody");

				let background0 = "transparent";
				let background1 = "rgba(0, 0, 0, 0.05)";
				let background2 = "rgba(0, 0, 0, 0.1)";

				section.clicked = false;
				section.addEventListener("click", function(){
					event.stopPropagation();
					if(section.clicked){
						DisplaySectionBody(section, "none");
						section.style.backgroundColor = background0;
					}
					else{
						DisplaySectionBody(section, "block");
						section.style.backgroundColor = background2;
					}
					section.clicked = !section.clicked;
				});
				section.addEventListener("mouseenter", function(){
					if(!section.clicked && hoverMode){
						DisplaySectionBody(section, "block");
						section.style.backgroundColor = background1;
					}
				});
				section.addEventListener("mouseleave", function(){
					if(!section.clicked && hoverMode){
						DisplaySectionBody(section, "none");
						section.style.backgroundColor = background0;
					}
				});
			}
		}
	});
	
}