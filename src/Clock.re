/* State declaration */
type state = string;

/* Action declaration */
type action =
  | Tick(string);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Clock");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => Js.Date.(make() |> toLocaleTimeString),
    /* State transitions */
    reducer: (action, state) =>
    switch (action) {
    | Tick(time) => ReasonReact.Update(time)
    },
  subscriptions: (self) => [
    Sub(
      () => Js.Global.setInterval(() => {
        let time = Js.Date.(make() |> toLocaleTimeString); 
        self.send(Tick(time));
      }, 1000),
      Js.Global.clearInterval
    )
  ],
  render: self => {
    <div>
     (ReasonReact.stringToElement(self.state))
    </div>;
  },
};
