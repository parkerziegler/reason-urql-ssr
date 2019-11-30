let options = ["20", "40", "60", "80", "100", "120", "140", "151"];

[@react.component]
let make = (~search, ~count, ~handleSearchChange, ~handleCountChange) => {
  <section className="controls">
    <div className="controls__input-container">
      <label htmlFor="search" className="controls__input-label">
        <strong> "Search Pokemon"->React.string </strong>
      </label>
      <input
        type_="text"
        value=search
        onChange=handleSearchChange
        className="controls__input"
        id="search"
      />
    </div>
    <select
      value={string_of_int(count)}
      onChange=handleCountChange
      className="controls__select">
      {options
       |> List.map(num =>
            <option key=num value=num> num->React.string </option>
          )
       |> Array.of_list
       |> React.array}
    </select>
  </section>;
};