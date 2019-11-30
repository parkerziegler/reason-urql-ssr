open ReasonUrql;

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

type state = {
  search: string,
  count: int,
};

type action =
  | SetSearch(string)
  | SetCount(int);

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetSearch(search) => {...state, search}
        | SetCount(count) => {...state, count}
        },
      {search: "", count: 20},
    );

  let handleSearchChange = ev => {
    dispatch(SetSearch(ReactEvent.Form.target(ev)##value));
  };

  let handleCountChange = ev => {
    dispatch(SetCount(ReactEvent.Form.target(ev)##value));
  };

  <>
    <Controls
      search={state.search}
      count={state.count}
      handleSearchChange
      handleCountChange
    />
    <PokemonGrid search={state.search} count={state.count} />
  </>;
};

let clientOptions:
  Client.clientOptions(option(Client.fetchOptions(Fetch.requestInit))) =
  Client.clientOptions(~url="https://graphql-pokemon.now.sh", ());

let default = (NextUrql.withUrqlClient(. clientOptions))(. make);