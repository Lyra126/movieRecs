import React, { useState } from 'react';
import './App.css';

function App() {
  // State variables to manage the selected values of each dropdown
  const [language, setLanguage] = useState('Select Language');
  const [genre, setGenre] = useState('Select Genre');
  const [length, setLength] = useState('Select Length');
  const [rating, setRating] = useState('Select Rating');
  const [year, setYear] = useState('Select Year');

  const [movieRecommendations, setMovieRecommendations] = useState({});

  // Function to handle changes in the dropdowns
  const handleDropdownChange = (category, value) => {
    switch (category) {
      case 'Language':
        setLanguage(value);
        break;
      case 'Genre':
        setGenre(value);
        break;
      case 'Length':
        setLength(value);
        break;
      case 'Rating':
        setRating(value);
        break;
      case 'Year':
        setYear(value);
        break;
      default:
        break;
    }
  };

  const logPreferences = () => {
    console.log('Button clicked!');
    const preferences = {
        Language: language !== 'Select Language' ? language : 'N/A',
        Genre: genre !== 'Select Genre' ? genre : 'N/A',
        Length: length !== 'Select Length' ? length : 'N/A',
        Rating: rating !== 'Select Rating' ? rating : 'N/A',
        Year: year !== 'Select Year' ? year : 'N/A',
    };       
    fetch('http://localhost:3000/preferences', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(preferences),
    })
        .then((response) => response.text())
        .then((data) => console.log('Response from server:', data))
        .catch((error) => console.error('Error:', error));

    setMovieRecommendations(preferences);
};

const displayMovieRecs = () => {
  document.getElementById("MovieContainer").innerHTML = '';
  fetch("movieRecs.txt")
      .then(response => response.text())
      .then(data => {
          // Assuming data is a string containing multiple entries
          const entries = data.split('\n').slice(0, 5); // Take only the first 5 entries

          // Create a container element to hold the movie entries
          const container = document.getElementById("MovieContainer");
          container.style.backgroundColor = '#ffcad4';
          container.style.marginLeft = '400px';
          container.style.marginRight = '100px';
        
          entries.forEach(entry => {
              try {
                  const movieObject = JSON.parse(`{${entry}}`);
                  const movieDiv = document.createElement('div');
                  const button = document.createElement('button');
                  const extraInfoDiv = document.createElement('div');
                  const image = document.createElement('img');
                  movieDiv.style.fontSize = 'x-large';
                  movieDiv.style.fontFamily = 'Verdana'
                  movieDiv.style.fontWeight = '5'
                  extraInfoDiv.style.fontSize = 'medium';
                  button.textContent = `Show Details`;
                  movieDiv.textContent = `${movieObject.movieTitle}  `;
                  movieDiv.appendChild(document.createElement('br'));
                  if(!(movieObject.poster.length == 0 || movieObject.poster.length == 3))
                    image.src = movieObject.poster; // Set the image source to the URL of the poster
                  image.style.width = '30%'; // Set the width of the image (adjust as needed)
                  image.style.height = '30%';
                  movieDiv.appendChild(image);
                  extraInfoDiv.textContent = `Year: ${movieObject.year}, Rated: ${movieObject.rated}, Genre: ${movieObject.genre}, Country: ${movieObject.country}, Director: ${movieObject.director}, Writers: ${movieObject.writer}, Actors: ${movieObject.actor}, Plot: ${movieObject.plot}, Awards: ${movieObject.award}, Metascore: ${movieObject.metascore}, Boxoffice: ${movieObject.boxoffice}, DVD: ${movieObject.DVD}`;
                  extraInfoDiv.style.display = 'none';

                  // Toggle display of extra info on button click
                  button.addEventListener('click', () => {
                      extraInfoDiv.style.display = extraInfoDiv.style.display === 'none' ? 'block' : 'none';
                  });
                  movieDiv.appendChild(document.createElement('br'));
                  movieDiv.appendChild(button);
                  container.appendChild(movieDiv);
                  container.appendChild(extraInfoDiv);
                  container.appendChild(document.createElement('br'));
              } catch (error) {
                  console.error("Error parsing JSON:", error);
              }
          });

          // Append the container to the body of the document
          document.body.appendChild(container);
      })
      .catch(error => console.error("Error fetching movie data:", error));
};

  return (
    <div className="App">
      <div className="left-section">
        <h2>Choose Your Preferences: </h2>

        {/* Language Dropdown */}
        <div className="dropdown-container">
          <label>Language: </label>
          <select value={language} onChange={(e) => handleDropdownChange('Language', e.target.value)}>
            <option value="Select Language">Select Language</option>
            <option value="English">English</option>
            <option value="Spanish">Spanish</option>
            <option value="French">French</option>
          </select>
        </div>

        {/* Genre Dropdown */}
        <div className="dropdown-container">
          <label>Genre: </label>
          <select value={genre} onChange={(e) => handleDropdownChange('Genre', e.target.value)}>
            <option value="Select Genre">Select Genre</option>
            <option value="Action">Action</option>
            <option value="Comedy">Comedy</option>
            <option value="Drama">Drama</option>
            <option value="Romance">Romance</option>
            <option value="History">History</option>
            <option value="Adventure">Adventure</option>
            <option value="Animation">Animation</option>
            <option value="Sci-Fi">Sci-Fi</option>
          </select>
        </div>

        {/* Length Dropdown */}
        <div className="dropdown-container">
          <label>Length: </label>
          <select value={length} onChange={(e) => handleDropdownChange('Length', e.target.value)}>
            <option value="Select Length">Select Length</option>
            <option value="60 mins">60 minutes</option>
            <option value="75 mins">75 minutes</option>
            <option value="90 mins">90 minutes</option>
            <option value="120 mins">120 minutes</option>
        
          </select>
        </div>

        {/* Age Rating Dropdown */}
        <div className="dropdown-container">
          <label>Age Rating: </label>
          <select value={rating} onChange={(e) => handleDropdownChange('Rating', e.target.value)}>
            <option value="Select Rating">Select Rating</option>
            <option value="G">G</option>
            <option value="PG">PG</option>
            <option value="PG-13">PG-13</option>
            <option value="R">R</option>
          </select>
        </div>

        {/* Year Dropdown */}
        <div className="dropdown-container">
          <label>Year Released: </label>
          <select value={year} onChange={(e) => handleDropdownChange('Year', e.target.value)}>
            <option value="Select Year">Select Year</option>
            <option value="2022-2023">2022-2023</option>
            <option value="2017-2022">2017-2022</option>
            <option value="2011-2016">2011-2016</option>
            <option value="2005-2010">2005-2010</option>
            <option value="1900 2005">1900-2005</option>
          </select>
        </div>

        {/* Button to log preferences */}
        <button onClick={logPreferences}>Log Preferences</button>
        <button onClick={displayMovieRecs}>Display Movies</button>
        <div id="MovieContainer" align = "center"></div>
        {Object.keys(movieRecommendations).length > 0 && (
          <div className="movie-recommendations">
            <h3>Movie Recommendations:</h3>
            {Object.entries(movieRecommendations).map(([category, value]) => (
              <div key={category}>{`${category}: ${value}`}</div>
            ))}
          </div>
        )}
      </div>

      {/* Main Section with Movie Recommendations */}
      <div className="main-section">
        <header className="App-header">
          <h2>Here are your movie recommendations:</h2>
        </header>
        {/* Add your movie recommendation content here */}
      </div>
    </div>
  );
}


export default App;