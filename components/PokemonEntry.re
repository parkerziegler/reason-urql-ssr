/* The Js.t type returned by the Pokemon GraphQL API. */
type pokemon = {
  .
  "id": string,
  "image": option(string),
  "name": option(string),
  "types": option(array(option(string))),
};

/* A map of types to icons to render for the Pokedex. A pokemon may
   have one or more types and we want to display the associated icon for
   each type in each pokemon's pane. */
let typeToIcon =
  Js.Dict.fromArray([|
    ("Bug", "/Bug@2x.png"),
    ("Dark", "/Dark@2x.png"),
    ("Dragon", "/Dragon@2x.png"),
    ("Electric", "/Electric@2x.png"),
    ("Fairy", "/Fairy@2x.png"),
    ("Fighting", "/Fight@2x.png"),
    ("Fire", "/Fire@2x.png"),
    ("Ghost", "/Ghost@2x.png"),
    ("Grass", "/Grass@2x.png"),
    ("Ground", "/Ground@2x.png"),
    ("Ice", "/Ice@2x.png"),
    ("Normal", "/Normal@2x.png"),
    ("Poison", "/Poison@2x.png"),
    ("Psychic", "/Psychic@2x.png"),
    ("Rock", "/Rock@2x.png"),
    ("Steel", "/Steel@2x.png"),
    ("Water", "/Water@2x.png"),
  |]);

external styleJsx: (~jsx: bool) => string = "";

[@react.component]
let make = (~pokemon) => {
  <div>
    <img
      src={pokemon##image->Belt.Option.getWithDefault("")}
      className="pokemon-image"
      alt={pokemon##name->Belt.Option.getWithDefault("")}
    />
    <h2> {pokemon##name->Belt.Option.getWithDefault("")->React.string} </h2>
    <div className="pokemon-types">
      {pokemon##types->Belt.Option.getWithDefault([||])
       |> Array.map(t => {
            let type_ = t->Belt.Option.getWithDefault("");
            switch (Js.Dict.get(typeToIcon, type_)) {
            | Some(typePath) =>
              <div className="pokemon-type">
                <img src=typePath className="pokemon-type-icon" alt=type_ />
                <span className="pokemon-type-text">
                  type_->React.string
                </span>
              </div>
            | None => React.null
            };
          })
       |> React.array}
    </div>
  </div>;
};