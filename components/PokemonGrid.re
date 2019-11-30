open ReasonUrql;
open Hooks;

module GetPokemon = [%graphql
  {|
query pokemon($first: Int!) {
    pokemons(first: $first) {
      id
      name
      types
      resistant
      weaknesses
      image
      evolutions {
        name
      }
    }
  }
|}
];

[@react.component]
let make = (~count, ~search) => {
  let request = GetPokemon.make(~first=count, ());
  let ({response}, _) = useQuery(~request, ());

  switch (response) {
  | Data(d) =>
    <div className="pokemon-grid">
      {switch (d##pokemons) {
       | Some(pkm) =>
         pkm
         |> Js.Array.filter(pokemon =>
              switch (pokemon) {
              | Some(p) =>
                String.length(search) > 0
                  ? {
                    Js.String.includes(
                      search |> String.lowercase_ascii,
                      Belt.Option.getWithDefault(p##name, "")
                      |> String.lowercase_ascii,
                    );
                  }
                  : true
              | None => false
              }
            )
         |> Array.map(pokemon =>
              switch (pokemon) {
              | Some(p) => <PokemonEntry pokemon=p key=p##id />
              | None => React.null
              }
            )
         |> React.array
       | None => React.null
       }}
    </div>
  | Error(e) => <div> e.message->React.string </div>
  | _ => React.null
  };
};