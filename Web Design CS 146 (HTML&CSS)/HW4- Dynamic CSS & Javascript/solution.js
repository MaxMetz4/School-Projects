// Here are the paths to the images
const fileLocations = {
   woofer: './img/woofer.jpg',
   pupper: './img/pupper.jpg',
   clouds: './img/clouds.jpg',
   snek: './img/snek.jpg'
};

/**
 * This function will get the values of the following elements:
 * 		formUsername, formCaption, formImg
 * Then, this will pass those values to the addNewPost function.
 * @param {Event} event the submit event of the #postForm form
 */
function handleFormSubmit(event) {
   // This next line prevents the reload of the form
   event.preventDefault();
   // Get values of inputs
   var x = document.getElementById("formUsername").value;
   var y = document.getElementById("formCaption").value;
   var z = document.getElementById("formImg").value;

   if(z == 'woofer'){
      z = fileLocations.woofer
   }
   if(z == 'pupper'){
      z =  fileLocations.pupper
   }
   if(z == 'clouds'){
      z =  fileLocations.clouds
   }
   if(z == 'snek'){
      z =  fileLocations.snek
   }
   // Pass values to addNewPost()
   addNewPost(x,y,z);
}  

/**
 * This function create the following div and append it to the #postList element
	<div class="post">
		<span>{username}</span>
		<img src="{imgLocation}" alt="{caption}">
		<div class="postOverlay">
			{caption}
		</div>
	</div>
 * 
 * Also, add a mouseover and mouseleave events to the post div element
 * @param {String} username username of the post
 * @param {String} caption caption of the post
 * @param {String} imgLocation location of the post image
 */
function addNewPost(username, caption) {
   // Create the parent post div
   let newDiv = document.createElement('div');
   newDiv.setAttribute('class', "post")
   // Create a span for the user
   let newSpan = document.createElement('span');
   newSpan.innerHTML = username;
   // Create image element
   let newImg = document.createElement('img');
   newImg.src = imgLocation;
   newImg.alt = caption;
   // Create overlay element
   let innerDiv = document.createElement('div');
   innerDiv.setAttribute('class', "postOverlay")   
   innerDiv.innerHTML = caption;
   // Add all child elements (order matters)
   newDiv.appendChild(newSpan);
   newDiv.appendChild(newImg);
   newDiv.appendChild(innerDiv);
   // Add event listeners to post
   newDiv.addEventListener('mouseover', function(){
      innerDiv.style. opacity = 1;
   });
   newDiv.addEventListener('mouseleave', function(){
      innerDiv.style. opacity = 0;
   });
   // Add post element to post list
   postList.appendChild(newDiv)
}

window.onload = () => {
   // Once our window is loaded, we add the event listener for our post form
   postForm.addEventListener('submit', handleFormSubmit);
};