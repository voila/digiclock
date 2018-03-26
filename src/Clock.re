/* This is the basic component. */
let component = ReasonReact.statelessComponent("Page");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  subscriptions: (self) => [
    Sub(
      () => Js.Global.setInterval(() => Js.Date.(make() |> toLocaleTimeString) |> Js.log, 1000),
      Js.Global.clearInterval
    )
  ],
  render: self => {
    <div>
     ReasonReact.nullElement
    </div>;
  },
};
