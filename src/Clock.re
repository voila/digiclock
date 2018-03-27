/* State declaration */
type state = int;

/* Action declaration */
type action =
  | Tick
  | Time(int);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Clock");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => 0,
    /* State transitions */
    reducer: (action, state) =>
    switch (action) {
    | Time(t) => 
      ReasonReact.Update(t)
    | Tick => 
      ReasonReact.Update(state + 1000)
    },
  subscriptions: (self) => [
    Sub(
      () => Js.Global.setInterval(() => {
        self.send(Tick);
      }, 1000),
      Js.Global.clearInterval
    ),
    /* Sub(
      () => Js.Global.setInterval(() => {
        Tzdb.getTimeMock(t => self.send(Time(t)))
        ;
      }, 5000),
      Js.Global.clearInterval 
    ),*/
    
  ],
  render: self => {
    let d = Js.Date.(self.state |> float_of_int |> fromFloat);
    <div id="digits">
     (ReasonReact.stringToElement(d |> Js.Date.toLocaleTimeString))
    </div>;
  },
};
